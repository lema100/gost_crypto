#ifndef _MAGMA_H_
#define _MAGMA_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#define MAGMA_KEY_SIZE		32
#define MAGMA_BLOCK_COUNT	32
#define MAGMA_BLOCK_SIZE	4
#define MAGMA_ADD_KEY_SIZE	8
#define MAGMA_DATA_SIZE		8

typedef struct
{
	uint8_t out[MAGMA_DATA_SIZE];
	uint8_t key_add1[MAGMA_ADD_KEY_SIZE];
	uint8_t key_add2[MAGMA_ADD_KEY_SIZE];
	uint8_t key_orig[MAGMA_KEY_SIZE];
} magma_ctx_t;

void Magma_Init(magma_ctx_t *ctx, const uint8_t *key);
void Magma_ECB_enc(magma_ctx_t *ctx, const uint8_t *blk);
void Magma_ECB_dec(magma_ctx_t *ctx, const uint8_t *blk);
void Magma_CTR(magma_ctx_t *ctx, const uint8_t *blk, const uint8_t *iv, uint8_t *out, uint32_t len);
void Magma_MIC(magma_ctx_t *ctx, const uint8_t *blk, uint32_t len);
void Magma_KEY_mesh(magma_ctx_t *parent, magma_ctx_t *child, uint8_t iv_base);

#ifdef __cplusplus
}
#endif

#endif
