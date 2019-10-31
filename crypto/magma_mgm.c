#include "magma_mgm.h"
#include "magma.h"

#include <string.h>
#include <stdint.h>

static void _memcpy(uint8_t *dst, const uint8_t *src, uint8_t len)
{
	for (uint8_t i = 0; i < len; i++)
		dst[i] = src[len - i - 1];
}

static void Inc_32(uint8_t *a)
{
	uint16_t internal = 0x0100;
	for (int8_t i = 3; i >= 0; i--)
	{
		internal = a[i] + (internal >> 8);
		a[i] = internal & 0xff;
	}
}

static void Gmul_64(const uint8_t *a, const uint8_t *b, uint8_t *c)
{
	uint64_t _a64, _b64, _c64 = 0;
	uint8_t *_a = (uint8_t *)&_a64;
	uint8_t *_b = (uint8_t *)&_b64;
	uint8_t *_c = (uint8_t *)&_c64;
	
	_memcpy(_a, a, 8);
	_memcpy(_b, b, 8);
	
	uint8_t hi;
	for (uint8_t i = 0; i < 64; i++)
	{
		if (_b[0] & 0x01)
			_c64 ^= _a64;
		hi = _a[7] & 0x80;
		_a64 <<= 1;
		if (hi)
			_a[0] ^= 0x1b;	//	x^64 + x^4 + x^3 + x + 1
		_b64 >>= 1;
	 }
	_memcpy(c, _c, 8);
}

static void mgm_premic(magma_ctx_t *ctx, uint8_t *nonce, const uint8_t *a, uint32_t len, uint8_t *t)
{
	uint32_t _len = 0, _delta = 0;
	uint64_t _acl64;
	uint8_t *_acl = (uint8_t *)&_acl64;
	while(len > _len)
	{
		_delta = len - _len;
		Magma_ECB_enc(ctx, nonce);
		if (_delta > MAGMA_DATA_SIZE)
		{
			Gmul_64(ctx->out, a + _len, _acl);
			_len += MAGMA_DATA_SIZE;
			Inc_32(&nonce[0]);
			*(uint64_t *)t ^= _acl64;
		}
		else
		{
			uint8_t tmp[MAGMA_DATA_SIZE];
			memset(tmp, 0x00, MAGMA_DATA_SIZE);
			memcpy(tmp, a + _len, _delta);
			Gmul_64(ctx->out, tmp, _acl);
			Inc_32(&nonce[0]);
			*(uint64_t *)t ^= _acl64;
			break;
		}
	}
}

void Magma_MGM_MIC(
	magma_ctx_t *ctx,
	const uint8_t *nonce,
	const uint8_t *c,
	const uint8_t *a,
	uint32_t len_c,
	uint32_t len_a,
	uint8_t *t)
{
	uint64_t _len64, _nonce64, _t64 = 0;
	uint8_t *_len = (uint8_t *)&_len64;
	uint8_t *_t = (uint8_t *)&_t64;
	uint8_t *_nonce = (uint8_t *)&_nonce64;
	
	memcpy(_nonce, nonce, MAGMA_DATA_SIZE);
	_nonce[0] |= 0x80;
	Magma_ECB_enc(ctx, _nonce);
	memcpy(_nonce, ctx->out, MAGMA_DATA_SIZE);

	mgm_premic(ctx, _nonce, a, len_a, _t);
	mgm_premic(ctx, _nonce, c, len_c, _t);

	len_c *= 8;
	len_a *= 8;
	_memcpy(&_len[0], (uint8_t *)&len_a, 4);
	_memcpy(&_len[4], (uint8_t *)&len_c, 4);

	Magma_ECB_enc(ctx, _nonce);
	Gmul_64(ctx->out, _len, _len);
	_t64 ^= _len64;
	Magma_ECB_enc(ctx, _t);
	
	memcpy(t, ctx->out, MAGMA_DATA_SIZE);
}

void Magma_MGM(
	magma_ctx_t *ctx,
	const uint8_t *nonce,
	const uint8_t *blk,
	uint32_t len,
	uint8_t *out)
{
	uint32_t _len = 0, _delta = 0;
	uint8_t _nonce[MAGMA_DATA_SIZE];

	memcpy(_nonce, nonce, MAGMA_DATA_SIZE);
	_nonce[0] &= 0x7F;
	Magma_ECB_enc(ctx, _nonce);
	memcpy(_nonce, ctx->out, MAGMA_DATA_SIZE);

	while(len > _len)
	{
		_delta = len - _len;
		Magma_ECB_enc(ctx, _nonce);
		if (_delta > MAGMA_DATA_SIZE)
		{
			for (uint8_t i = 0; i < 8; i++)
				out[_len + i] = blk[_len + i] ^ ctx->out[i];
			_len += MAGMA_DATA_SIZE;
			Inc_32(&_nonce[4]);
		}
		else
		{
			for (uint8_t i = 0; i < _delta; i++)
				out[_len + i] = blk[_len + i] ^ ctx->out[i];
			break;
		}
	}
}
