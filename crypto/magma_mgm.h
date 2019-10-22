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

#ifdef __cplusplus
}
#endif

#endif
