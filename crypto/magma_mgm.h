#ifndef _MAGMA_MGM_H_
#define _MAGMA_MGM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "magma.h"

void Magma_MGM(
	magma_ctx_t *ctx,
	const uint8_t *nonce,
	const uint8_t *blk,
	uint32_t len,
	uint8_t *out);

void Magma_MGM_MIC(
	magma_ctx_t *ctx,
	const uint8_t *nonce,
	const uint8_t *c,
	const uint8_t *a,
	uint32_t len_c,
	uint32_t len_a,
	uint8_t *t);

#ifdef __cplusplus
}
#endif

#endif
