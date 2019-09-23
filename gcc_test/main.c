#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include "../crypto/stribog.h"
#include "../crypto/magma.h"

void test(const uint8_t * data0, const uint8_t * data1, uint8_t len)
{
	uint8_t fail = 0;
	for (uint8_t i = 0; i < len; i++)
		if (data0[i] != data1[i])
			fail++;
	
	if (fail)
		printf("TEST FAIL %d\n", fail);
	else
		printf("TEST OK\n");
}

void print_bytes(const uint8_t * data, uint8_t len)
{
	printf("0x");
	for (uint8_t i = 0; i < len; i++)
		printf("%02X", data[i]);
	printf("\n");
}

void print_hash(stribog_ctx_t *ctx)
{
	print_bytes(ctx->h, ctx->size ? STRIBOG_OUTPUT_SIZE_512 : STRIBOG_OUTPUT_SIZE_256);
}

void test_hash(stribog_ctx_t *ctx, const uint8_t * data)
{
	test(ctx->h, data, ctx->size ? STRIBOG_OUTPUT_SIZE_512 : STRIBOG_OUTPUT_SIZE_256);
}

int main(int argn, char *argc[])
{
	magma_ctx_t ctx_magma;
	stribog_ctx_t ctx_stribog;

	Magma_Init(&ctx_magma, key);
	
	printf("\nMagma tests\n");
	printf("\nExpanded kyes\n");
	for (uint8_t i = 0; i < 4; i++)
	{
		for (uint8_t j = 0; j < 8; j++)
			print_bytes(ctx_magma.key_iter[i * 8 + j], 4);
		printf("\n");
	}
	
	printf("Additional key K1\t");
	print_bytes(ctx_magma.k1, 8);
	printf("Additional key K2\t");
	print_bytes(ctx_magma.k2, 8);
	printf("\n");

	for(uint8_t i = 0; i < 5; i++)
	{
		Magma_ECB_enc(&ctx_magma, data[i]);
		printf("Encrypted message %d\t", i);
		print_bytes(ctx_magma.out, 8);

		test(data_enc_test[i], ctx_magma.out, 8);

		Magma_ECB_dec(&ctx_magma, ctx_magma.out);
		printf("Decrypted message %d\t", i);
		print_bytes(ctx_magma.out, 8);	

		printf("Original message %d\t", i);
		print_bytes(data[i], 8);
		
		test(data[i], ctx_magma.out, 8);
		printf("\n");
	}

	ctx_magma.padded = 0;
	ctx_magma.blk_len = 4;
	
	Magma_MIC(&ctx_magma, &data[1]);
	printf("MIC of message\t\t");
	print_bytes(ctx_magma.out, 4);
	test(mic_test, ctx_magma.out, 4);

	printf("\n\nStribog tests\n\n");
	
	stribog_init(&ctx_stribog, STRIBOG_HASH512);
	stribog_calc(&ctx_stribog, message0, sizeof(message0));
	printf("Message 0 H^{512}\t");
	print_hash(&ctx_stribog);
	test_hash(&ctx_stribog, message0_test[0]);

	stribog_init(&ctx_stribog, STRIBOG_HASH256);
	stribog_calc(&ctx_stribog, message0, sizeof(message0));
	printf("Message 0 H^{256}\t");
	print_hash(&ctx_stribog);
	test_hash(&ctx_stribog, message0_test[1]);

	stribog_init(&ctx_stribog, STRIBOG_HASH512);
	stribog_calc(&ctx_stribog, message1, sizeof(message1));
	printf("\nMessage 1 H^{512}\t");
	print_hash(&ctx_stribog);
	test_hash(&ctx_stribog, message1_test[0]);

	stribog_init(&ctx_stribog, STRIBOG_HASH256);
	stribog_calc(&ctx_stribog, message1, sizeof(message1));
	printf("Message 1 H^{256}\t");
	print_hash(&ctx_stribog);
	test_hash(&ctx_stribog, message1_test[1]);

	return 1;
}









