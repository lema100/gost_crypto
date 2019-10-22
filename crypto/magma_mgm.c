#include "magma_mgm.h"
#include "magma.h"

#include <string.h>
#include <stdint.h>

static void Inc_32(uint8_t *a)
{
	uint16_t internal = a[7] + 1;
	a[7] = internal & 0xff;
	for (int8_t i = 3; i >= 0; i--)
	{
		internal = a[i] + (internal >> 8);
		a[i] = internal & 0xff;
	}
}

void Magma_MGM_MIC(
	magma_ctx_t *ctx,
	const uint8_t *nonce,
	const uint8_t *c,
	const uint8_t *a,
	uint32_t len_a,
	uint32_t len_c,
	uint8_t *t)
{
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
	ctx->out[7] &= 0x7F;
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
			Inc_32(&_nonce[0]);
		}
		else
		{
			for (uint8_t i = 0; i < _delta; i++)
				out[_len + i] = blk[_len + i] ^ ctx->out[i];
			break;
		}
	}
}
