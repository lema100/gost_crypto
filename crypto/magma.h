#ifndef _MAGMA_H_
#define _MAGMA_H_

#include <string.h>
#include <stdint.h>

#define MAGMA_KEY_SIZE		32
#define MAGMA_BLOCK_SIZE	4
#define MAGMA_BLOCK_COUNT	32

typedef struct
{
	uint8_t out[8];
	uint8_t k1[8], k2[8];
	uint8_t padded, blk_len;
	uint8_t key_orig[MAGMA_KEY_SIZE];
	uint8_t key_iter[MAGMA_BLOCK_COUNT][MAGMA_BLOCK_SIZE];
} magma_ctx_t;

void Magma_Init(magma_ctx_t *ctx, const uint8_t *key);
void Magma_ECB_enc(magma_ctx_t *ctx, const uint8_t *blk);
void Magma_ECB_dec(magma_ctx_t *ctx, const uint8_t *blk);
void Magma_MIC(magma_ctx_t *ctx, const uint8_t *blk[]);

#endif
