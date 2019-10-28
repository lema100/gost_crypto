#include "magma_mgm.h"
#include "magma.h"

#include <string.h>
#include <stdint.h>

static void shl_64(uint8_t *data, uint8_t i)
{
	uint64_t tmp = data[0];

	for (uint8_t i = 1; i < 8; i++)
		tmp = (tmp << 8) + data[i];
	
	tmp <<= i;
	
	for (uint8_t i = 0; i < 8; i++)
		data[i] = tmp >> (56 - i * 8);
}


static void shr_64(uint8_t *data, uint8_t i)
{
	uint64_t tmp = data[0];

	for (uint8_t i = 1; i < 8; i++)
		tmp = (tmp << 8) + data[i];
	
	tmp >>= i;
	
	for (uint8_t i = 0; i < 8; i++)
		data[i] = tmp >> (56 - i * 8);
}

static void Xor_64(const uint8_t *a, const uint8_t *b, uint8_t *c)
{
	for (uint8_t i = 0; i < 8; i++)
		c[i] = a[i] ^ b[i];
}

/*
uint64_t Gmul(uint64_t a, uint64_t b)
{
	uint64_t p = 0;
	uint8_t hi;
	for (uint8_t i = 0; i < 64; i++)
	{
		if (b & (uint64_t)0x01)
			p ^= a;
		hi = (a & 0x8000000000000000) ? 1 : 0;
		a <<= 1;
		if (hi)
			a ^= (uint64_t)0x1b;	//	x^64 + x^4 + x^3 + x + 1
		b >>= 1;
	}
	return p;
}
*/

static void Gmul_64(const uint8_t *a, const uint8_t *b, uint8_t *c)
{
	uint8_t _a[8], _b[8];
	
	memcpy(_a, a, 8);
	memcpy(_b, b, 8);
	memset(c, 0x00, 8);
	
	uint8_t hi;
	for (uint8_t i = 0; i < 64; i++)
	{
		if (_b[7] & 0x01)
			Xor_64(c, _a, c);
		hi = _a[0] & 0x80;
		shl_64(_a, 1);
		if (hi)
			_a[7] ^= 0x1b;	/* x^64 + x^4 + x^3 + x + 1 */
		shr_64(_b, 1);
	}
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

static void mgm_premic(magma_ctx_t *ctx, uint8_t *nonce, const uint8_t *a, uint32_t len, uint8_t *t)
{
	uint32_t _len = 0, _delta = 0;
	uint8_t acl[MAGMA_DATA_SIZE];
	while(len > _len)
	{
		_delta = len - _len;
		Magma_ECB_enc(ctx, nonce);
		if (_delta > MAGMA_DATA_SIZE)
		{
			Gmul_64(ctx->out, a + _len, acl);
			_len += MAGMA_DATA_SIZE;
			Inc_32(&nonce[0]);
			Xor_64(t, acl, t);
		}
		else
		{
			uint8_t tmp[MAGMA_DATA_SIZE];
			memset(tmp, 0x00, MAGMA_DATA_SIZE);
			memcpy(tmp, a + _len, _delta);
			Gmul_64(ctx->out, tmp, acl);
			Inc_32(&nonce[0]);
			Xor_64(t, acl, t);
			break;
		}
	}
}

static void _memcpy(uint8_t *dst, uint8_t *src, uint8_t len)
{
	for (uint8_t i = 0; i < len; i++)
		dst[i] = src[len - i - 1];
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
	uint8_t _nonce[MAGMA_DATA_SIZE];
	
	memcpy(_nonce, nonce, MAGMA_DATA_SIZE);
	_nonce[0] |= 0x80;
	Magma_ECB_enc(ctx, _nonce);
	memcpy(_nonce, ctx->out, MAGMA_DATA_SIZE);

	memset(t, 0x00, MAGMA_DATA_SIZE);
	mgm_premic(ctx, _nonce, a, len_a, t);
	mgm_premic(ctx, _nonce, c, len_c, t);

	uint8_t tmp[MAGMA_DATA_SIZE];
	len_c *= 8;
	len_a *= 8;
	_memcpy(&tmp[0], (uint8_t *)&len_a, 4);
	_memcpy(&tmp[4], (uint8_t *)&len_c, 4);

	Magma_ECB_enc(ctx, _nonce);
	Gmul_64(ctx->out, tmp, tmp);
	Xor_64(t, tmp, t);
	Magma_ECB_enc(ctx, t);
	
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
