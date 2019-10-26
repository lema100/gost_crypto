#include "main.h"

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "../crypto/stribog.h"
#include "../crypto/magma_mgm.h"
#include "../crypto/magma.h"

void test(const uint8_t * data0, const uint8_t * data1, uint32_t len)
{
	uint32_t fail = 0;
	for (uint32_t i = 0; i < len; i++)
		if (data0[i] != data1[i])
			fail++;
	
	if (fail)
		printf(ANSI_COLOR_RED "TEST FAIL %d\n" ANSI_COLOR_RESET, fail);
	else
		printf(ANSI_COLOR_GREEN "TEST OK\n" ANSI_COLOR_RESET);
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
	
	printf(ANSI_COLOR_MAGENTA "\nMagma tests\n" ANSI_COLOR_RESET);
	printf("\nAdditional key 1\t");
	print_bytes(ctx_magma.key_add1, sizeof(ctx_magma.key_add1));
	printf("Additional key 2\t");
	print_bytes(ctx_magma.key_add2, sizeof(ctx_magma.key_add2));
	printf("\n");

	for(uint8_t i = 0; i < 5; i++)
	{
		Magma_ECB_enc(&ctx_magma, data[i]);
		printf("Encrypted message %d\t", i);
		print_bytes(ctx_magma.out, sizeof(ctx_magma.out));

		test(data_enc_test[i], ctx_magma.out, sizeof(ctx_magma.out));

		Magma_ECB_dec(&ctx_magma, ctx_magma.out);
		printf("Decrypted message %d\t", i);
		print_bytes(ctx_magma.out, sizeof(ctx_magma.out));

		printf("Original message %d\t", i);
		print_bytes(data[i], sizeof(ctx_magma.out));
		
		test(data[i], ctx_magma.out, sizeof(ctx_magma.out));
		printf("\n");
	}

	Magma_MIC(&ctx_magma, &data[1], 4, 0);
	printf("MIC of message 4 block\t");
	print_bytes(ctx_magma.out, 4);
	test(mic_test[0], ctx_magma.out, 4);

	Magma_MIC(&ctx_magma, &data[1], 2, 0);
	printf("MIC of message 2 block\t");
	print_bytes(ctx_magma.out, 4);
	test(mic_test[1], ctx_magma.out, 4);

	printf(ANSI_COLOR_MAGENTA "\n\nStribog tests\n\n" ANSI_COLOR_RESET);

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

	printf("\nRoot magma key\t\t");
	print_bytes(ctx_magma.key_orig, sizeof(ctx_magma.key_orig));

	stribog_init(&ctx_stribog, STRIBOG_HASH256);
	stribog_calc(&ctx_stribog, key, sizeof(key));
	printf("Root magma key H^{256}\t");
	print_hash(&ctx_stribog);

	uint8_t tmp[MAGMA_DATA_SIZE * 4];
	uint8_t out[MAGMA_DATA_SIZE * 4];
	memset(out, 0, MAGMA_DATA_SIZE * 4);
	
	for(uint8_t i = 0; i < 4; i++)
		memcpy(&tmp[i * MAGMA_DATA_SIZE], data[1 + i], MAGMA_DATA_SIZE);
	
	Magma_CTR(&ctx_magma, tmp, data_ctr_iv, out, MAGMA_DATA_SIZE * 4);

	printf(ANSI_COLOR_MAGENTA "\nCTR" ANSI_COLOR_RESET);
	printf("\ninput:\n");
	for(uint8_t i = 0; i < 4; i++)
		print_bytes(&tmp[i * MAGMA_DATA_SIZE], MAGMA_DATA_SIZE);

	printf("\nencrypted:\n");
	for(uint8_t i = 0; i < 4; i++)
		print_bytes(&out[i * MAGMA_DATA_SIZE], MAGMA_DATA_SIZE);
	for(uint8_t i = 0; i < 4; i++)
		test(data_ctr_test[i + 1], &out[i * MAGMA_DATA_SIZE], MAGMA_DATA_SIZE);

	memset(tmp, 0, MAGMA_DATA_SIZE * 4);

	Magma_CTR(&ctx_magma, out, data_ctr_iv, tmp, MAGMA_DATA_SIZE * 4);

	printf("\ndecrypted:\n");
	for(uint8_t i = 0; i < 4; i++)
		print_bytes(&tmp[i * MAGMA_DATA_SIZE], MAGMA_DATA_SIZE);
	for(uint8_t i = 0; i < 4; i++)
		test(data[i + 1], &tmp[i * MAGMA_DATA_SIZE], MAGMA_DATA_SIZE);

	memset(out, 0, MAGMA_DATA_SIZE * 4);
	memcpy(tmp, data[0], MAGMA_DATA_SIZE);
	
	Magma_CTR(&ctx_magma, tmp, data_ctr_iv, out, MAGMA_DATA_SIZE);

	printf(ANSI_COLOR_MAGENTA "\nCTR" ANSI_COLOR_RESET);
	printf("\ninput:\n");
	print_bytes(tmp, MAGMA_DATA_SIZE);

	printf("\nencrypted:\n");
	print_bytes(out, MAGMA_DATA_SIZE);
	test(data_ctr_test[0], out, MAGMA_DATA_SIZE);

	memset(tmp, 0, MAGMA_DATA_SIZE * 4);

	Magma_CTR(&ctx_magma, out, data_ctr_iv, tmp, MAGMA_DATA_SIZE);

	printf("\noutput:\n");
	print_bytes(tmp, MAGMA_DATA_SIZE);
	test(data[0], tmp, MAGMA_DATA_SIZE);

	for (uint8_t j = 0; j < 6; j++)
	{
		uint8_t mgm_enc[mgm_p_size[j]], mgm_dec[mgm_p_size[j]];
		uint8_t mgm_t[MAGMA_DATA_SIZE];
		printf(ANSI_COLOR_MAGENTA "\nMGM %d" ANSI_COLOR_RESET, j);
		magma_ctx_t ctx_magma_mgm;
		Magma_Init(&ctx_magma_mgm, mgm_key[j]);
		Magma_MGM(&ctx_magma_mgm, mgm_nonce[j], mgm_p[j], mgm_p_size[j], mgm_enc);
		
		printf("\ninput:\n");
		print_bytes(mgm_p[j], mgm_p_size[j]);

		printf("\nencrypted:\n");
		print_bytes(mgm_enc, mgm_p_size[j]);
		test(mgm_test[j], mgm_enc, mgm_p_size[j]);

		Magma_MGM(&ctx_magma_mgm, mgm_nonce[j], mgm_enc, mgm_p_size[j], mgm_dec);

		printf("\ndecrypted:\n");
		print_bytes(mgm_dec, mgm_p_size[j]);
		test(mgm_p[j], mgm_dec, mgm_p_size[j]);
		
		Magma_MGM_MIC(&ctx_magma_mgm, mgm_nonce[j], mgm_test[j], mgm_a[j], mgm_p_size[j], mgm_a_size[j], mgm_t);
		
		printf("\nMIC:\n");
		print_bytes(mgm_t, MAGMA_DATA_SIZE);
		test(mgm_mic_test[j], mgm_t, MAGMA_DATA_SIZE);
	}

	FILE *file[3];
	const char *fname[] = {"Binary", "EncBinary5", "EncBinary6"};
	char *fdata[3];
	uint32_t flen[3];
	for (uint8_t i = 0; i < 3; i++)
	{
		if ((file[i] = fopen(fname[i], "rb+")) == NULL)
		{
			flen[i] = 0;
			continue;
		}
		fseek(file[i], 0, SEEK_END); 
		flen[i] = ftell(file[i]);
		fseek(file[i], 0, SEEK_SET); 
		
		fdata[i] = malloc(flen[i]);
		fread(fdata[i], 1, flen[i], file[i]);
	}

	for (uint8_t j = 0; j < 2; j++)
	{
		uint8_t mgm_t[MAGMA_DATA_SIZE];
		char *fenc, *fdec;
		fdec = fenc = malloc(flen[j + 1]);
		printf(ANSI_COLOR_MAGENTA "\nMGM files %d, len %d" ANSI_COLOR_RESET, j, flen[j + 1]);

		magma_ctx_t ctx_magma_mgm;
		Magma_Init(&ctx_magma_mgm, mgm_key_file[j]);

		Magma_MGM(&ctx_magma_mgm, mgm_nonce_file[j], (uint8_t *)fdata[0], flen[0], (uint8_t *)fenc);
		printf("\nencrypted:\n");
		test((uint8_t *)fenc, (uint8_t *)fdata[j + 1], flen[j + 1]);

		Magma_MGM(&ctx_magma_mgm, mgm_nonce_file[j], (uint8_t *)fdata[j + 1], flen[j + 1], (uint8_t *)fdec);
		printf("\ndecrypted:\n");
		test((uint8_t *)fdec, (uint8_t *)fdata[0], flen[0]);

		Magma_MGM_MIC(&ctx_magma_mgm, mgm_nonce_file[j], (uint8_t *)fdata[j + 1], mgm_t, flen[j + 1], 0, mgm_t);
		printf("\nMIC:\n");
		print_bytes(mgm_t, MAGMA_DATA_SIZE);
		test(mgm_t, mgm_mic_test_file[j], MAGMA_DATA_SIZE);
	}
	
	return 1;
}















