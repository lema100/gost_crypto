#include "magma.h"

static const unsigned char Pi[8][16] = 
{
	{1, 7, 14, 13, 0, 5, 8, 3, 4, 15, 10, 6, 9, 12, 11, 2},
	{8, 14, 2, 5, 6, 9, 1, 12, 15, 4, 11, 0, 13, 10, 3, 7},
	{5, 13, 15, 6, 9, 2, 12, 10, 11, 7, 8, 1, 4, 3, 14, 0},
	{7, 15, 5, 10, 8, 1, 6, 13, 0, 9, 3, 14, 11, 4, 2, 12},
	{12, 8, 2, 1, 13, 4, 15, 6, 7, 0, 10, 5, 3, 14, 9, 11},
	{11, 3, 5, 8, 2, 15, 10, 13, 14, 1, 7, 4, 12, 9, 6, 0},
	{6, 8, 2, 3, 9, 10, 5, 12, 1, 14, 4, 7, 11, 13, 0, 15},
	{12, 4, 6, 2, 10, 5, 11, 9, 14, 8, 13, 7, 0, 3, 15, 1}
};

static void GOST_Magma_Xor_32(const uint8_t *a, const uint8_t *b, uint8_t *c)
{
	for (uint8_t i = 0; i < 4; i++)
		c[i] = a[i] ^ b[i];
}

static void GOST_Magma_Xor_64(const uint8_t *a, const uint8_t *b, uint8_t *c)
{
	for (uint8_t i = 0; i < 8; i++)
		c[i] = a[i] ^ b[i];
}

static void GOST_Magma_Add_32(const uint8_t *a, const uint8_t *b, uint8_t *c)
{
	uint16_t internal = 0;
	for (int8_t i = 3; i >= 0; i--)
	{
		internal = a[i] + b[i] + (internal >> 8);
		c[i] = internal & 0xff;
	}
}

static void GOST_Magma_T(const uint8_t *in_data, uint8_t *out_data)
{
	uint8_t first_part_byte, sec_part_byte;

	for (uint8_t i = 0; i < 4; i++)
	{
		first_part_byte = (in_data[i] & 0xf0) >> 4;
		sec_part_byte = (in_data[i] & 0x0f);
		first_part_byte = Pi[i * 2][first_part_byte];
		sec_part_byte = Pi[i * 2 + 1][sec_part_byte];
		out_data[i] = (first_part_byte << 4) | sec_part_byte;
	}
}

static void GOST_Magma_g(const uint8_t *k, const uint8_t *a, uint8_t *out_data)
{
	uint8_t internal[4];
	uint32_t out_data_32;

	GOST_Magma_Add_32(a, k, internal);

	GOST_Magma_T(internal, internal);

	out_data_32 = internal[0];
	out_data_32 = (out_data_32 << 8) + internal[1];
	out_data_32 = (out_data_32 << 8) + internal[2];
	out_data_32 = (out_data_32 << 8) + internal[3];

	out_data_32 = (out_data_32 << 11)|(out_data_32 >> 21);

	out_data[3] = out_data_32;
	out_data[2] = out_data_32 >> 8;
	out_data[1] = out_data_32 >> 16;
	out_data[0] = out_data_32 >> 24;
}

static void GOST_Magma_G(const uint8_t *k, const uint8_t *a, uint8_t *out_data)
{
	uint8_t a_0[4];
	uint8_t a_1[4];
	uint8_t G[4];

	memcpy(a_0, a + 4, 4);
	memcpy(a_1, a, 4);

	GOST_Magma_g(k, a_0, G);
	GOST_Magma_Xor_32(a_1, G, G);

	memcpy(out_data, a_0, 4);
	memcpy(out_data + 4, G, 4);
}

static void GOST_Magma_G_Fin(const uint8_t *k, const uint8_t *a, uint8_t *out_data)
{
	uint8_t a_0[4];
	uint8_t a_1[4];
	uint8_t G[4];

	memcpy(a_0, a + 4, 4);
	memcpy(a_1, a, 4);

	GOST_Magma_g(k, a_0, G);
	GOST_Magma_Xor_32(a_1, G, G);

	memcpy(out_data, G, 4);
	memcpy(out_data + 4, a_0, 4);
}

static void shl_64(uint8_t *data, uint8_t i)
{
	uint64_t tmp = data[0];

	for (uint8_t i = 1; i < 8; i++)
		tmp = (tmp << 8) + data[i];
	
	tmp <<= i;
	
	for (uint8_t i = 0; i < 8; i++)
		data[i] = tmp >> (56 - i * 8);
}

void GOST_Magma_Init(magma_ctx_t *ctx, const uint8_t *key)
{
	memcpy(ctx->key_orig, key, KEY_SIZE);

	for(uint8_t i = 0; i < 24; i++)
		memcpy(ctx->key_iter[i], key + i % 8 * 4, 4);

	for(uint8_t i = 0; i < 8; i++)
		memcpy(ctx->key_iter[24 + i], key + (28 - i * 4), 4);

	uint8_t data[8];
	memset(data, 0x00, 8);
	GOST_Magma_ECB_enc(ctx, data, data);

	if (data[0] & 0x80)
	{
		shl_64(data, 1);
		data[7] ^= 0x33;
	}
	else
		shl_64(data, 1);
	memcpy(ctx->k1, data, 8);

	if (data[0] & 0x80)
	{
		shl_64(data, 1);
		data[7] ^= 0x33;
	}
	else
		shl_64(data, 1);
	memcpy(ctx->k2, data, 8);
}

void GOST_Magma_ECB_enc(magma_ctx_t *ctx, const uint8_t *blk, uint8_t *out_blk)
{
	if (blk != out_blk)
		memcpy(out_blk, blk, 8);

	for(uint8_t i = 0; i < 31; i++)
		GOST_Magma_G(ctx->key_iter[i], out_blk, out_blk);
	GOST_Magma_G_Fin(ctx->key_iter[31], out_blk, out_blk);
}

void GOST_Magma_ECB_dec(magma_ctx_t *ctx, const uint8_t *blk, uint8_t *out_blk)
{
	if (blk != out_blk)
		memcpy(out_blk, blk, 8);

	for(uint8_t i = 31; i > 0; i--)
		GOST_Magma_G(ctx->key_iter[i], out_blk, out_blk);
	GOST_Magma_G_Fin(ctx->key_iter[0], out_blk, out_blk);
}

void GOST_Magma_MIC(magma_ctx_t *ctx, const uint8_t *blk[], uint8_t blk_len, uint8_t padded, uint8_t *out_blk)
{
	memset(out_blk, 0x00, 8);
	for(uint8_t i = 0; i < blk_len; i++)
	{
		GOST_Magma_Xor_64(out_blk, blk[i], out_blk);
		
		if (i == blk_len - 1)
		{
			if (padded) 
				GOST_Magma_Xor_64(out_blk, ctx->k2, out_blk);
			else
				GOST_Magma_Xor_64(out_blk, ctx->k1, out_blk);
		}
		GOST_Magma_ECB_enc(ctx, out_blk, out_blk);
	}
}
