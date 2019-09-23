#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include "../crypto/magma.h"

const uint8_t key[] = 
{
	0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
	0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
	0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
	0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
};

const uint8_t *data[] = 
{
	(uint8_t []){0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10},
	(uint8_t []){0x92, 0xde, 0xf0, 0x6b, 0x3c, 0x13, 0x0a, 0x59},
	(uint8_t []){0xdb, 0x54, 0xc7, 0x04, 0xf8, 0x18, 0x9d, 0x20},
	(uint8_t []){0x4a, 0x98, 0xfb, 0x2e, 0x67, 0xa8, 0x02, 0x4c},
	(uint8_t []){0x89, 0x12, 0x40, 0x9b, 0x17, 0xb5, 0x7e, 0x41}
};

const uint8_t *data_enc_test[] = 
{
	(uint8_t []){0x4e, 0xe9, 0x01, 0xe5, 0xc2, 0xd8, 0xca, 0x3d},
	(uint8_t []){0x2b, 0x07, 0x3f, 0x04, 0x94, 0xf3, 0x72, 0xa0},
	(uint8_t []){0xde, 0x70, 0xe7, 0x15, 0xd3, 0x55, 0x6e, 0x48},
	(uint8_t []){0x11, 0xd8, 0xd9, 0xe9, 0xea, 0xcf, 0xbc, 0x1e},
	(uint8_t []){0x7c, 0x68, 0x26, 0x09, 0x96, 0xc6, 0x7e, 0xfb}
};

const uint8_t mic_test[] = {0x15, 0x4e, 0x72, 0x10};

static void test(const uint8_t * data0, const uint8_t * data1, uint8_t len)
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

static void print_bytes(const uint8_t * data, uint8_t len)
{
	printf("0x");
	for (uint8_t i = 0; i < len; i++)
		printf("%02X", data[i]);
	printf("\n");
}

int main(int argn, char *argc[])
{
	magma_ctx_t ctx;
	
	Magma_Init(&ctx, key);
	
	printf("\nExpanded kyes\n");
	for (uint8_t i = 0; i < 4; i++)
	{
		for (uint8_t j = 0; j < 8; j++)
			print_bytes(ctx.key_iter[i * 8 + j], 4);
		printf("\n");
	}
	
	printf("Additional key K1\t");
	print_bytes(ctx.k1, 8);
	printf("Additional key K2\t");
	print_bytes(ctx.k2, 8);
	printf("\n");

	for(uint8_t i = 0; i < 5; i++)
	{
		Magma_ECB_enc(&ctx, data[i]);
		printf("Encrypted message %d\t", i);
		print_bytes(ctx.out, 8);

		test(data_enc_test[i], ctx.out, 8);

		Magma_ECB_dec(&ctx, ctx.out);
		printf("Decrypted message %d\t", i);
		print_bytes(ctx.out, 8);

		printf("Original message %d\t", i);
		print_bytes(data[i], 8);
		
		test(data[i], ctx.out, 8);
		printf("\n");
	}

	ctx.padded = 0;
	ctx.blk_len = 4;
	
	Magma_MIC(&ctx, &data[1]);
	printf("MIC of message\t\t");
	print_bytes(ctx.out, 4);

	test(mic_test, ctx.out, 4);

	return 1;
}
