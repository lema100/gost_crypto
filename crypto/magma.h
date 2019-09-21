#ifndef _MAGMA_H_
#define _MAGMA_H_

#include <string.h>
#include <stdint.h>

#define KEY_SIZE	32
#define BLOCK_SIZE	4
#define BLOCK_COUNT	32

typedef struct
{
	uint8_t k1[8], k2[8];
	uint8_t key_orig[KEY_SIZE];
	uint8_t key_iter[BLOCK_COUNT][BLOCK_SIZE];
} magma_ctx_t;

void GOST_Magma_Init(magma_ctx_t *ctx, const uint8_t *key);
void GOST_Magma_ECB_enc(magma_ctx_t *ctx, const uint8_t *blk, uint8_t *out_blk);
void GOST_Magma_ECB_dec(magma_ctx_t *ctx, const uint8_t *blk, uint8_t *out_blk);
void GOST_Magma_MIC(magma_ctx_t *ctx, const uint8_t *blk[], uint8_t blk_len, uint8_t padded, uint8_t *out_blk);

#endif