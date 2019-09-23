#ifndef _DATA_SET_H
#define _DATA_SET_H

#include <stdint.h>

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

const uint8_t *mic_test[] =
{
	(uint8_t []){0x15, 0x4e, 0x72, 0x10},
	(uint8_t []){0x75, 0xe5, 0x7e, 0x64}
};

const uint8_t message0[] =
{
	0x32, 0x31, 0x30, 0x39, 0x38, 0x37, 0x36, 0x35,
	0x34, 0x33, 0x32, 0x31, 0x30, 0x39, 0x38, 0x37,
	0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x39,
	0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31,
	0x30, 0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33,
	0x32, 0x31, 0x30, 0x39, 0x38, 0x37, 0x36, 0x35,
	0x34, 0x33, 0x32, 0x31, 0x30, 0x39, 0x38, 0x37,
	0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30
};

const uint8_t message1[] =
{
	0xfb, 0xe2, 0xe5, 0xf0, 0xee, 0xe3, 0xc8, 0x20,
	0xfb, 0xea, 0xfa, 0xeb, 0xef, 0x20, 0xff, 0xfb,
	0xf0, 0xe1, 0xe0, 0xf0, 0xf5, 0x20, 0xe0, 0xed,
	0x20, 0xe8, 0xec, 0xe0, 0xeb, 0xe5, 0xf0, 0xf2,
	0xf1, 0x20, 0xff, 0xf0, 0xee, 0xec, 0x20, 0xf1,
	0x20, 0xfa, 0xf2, 0xfe, 0xe5, 0xe2, 0x20, 0x2c,
	0xe8, 0xf6, 0xf3, 0xed, 0xe2, 0x20, 0xe8, 0xe6,
	0xee, 0xe1, 0xe8, 0xf0, 0xf2, 0xd1, 0x20, 0x2c,
	0xe8, 0xf0, 0xf2, 0xe5, 0xe2, 0x20, 0xe5, 0xd1
};

const uint8_t *message0_test[] =
{
	(uint8_t []){
		0x48, 0x6f, 0x64, 0xc1, 0x91, 0x78, 0x79, 0x41,
		0x7f, 0xef, 0x08, 0x2b, 0x33, 0x81, 0xa4, 0xe2,
		0x11, 0xc3, 0x24, 0xf0, 0x74, 0x65, 0x4c, 0x38,
		0x82, 0x3a, 0x7b, 0x76, 0xf8, 0x30, 0xad, 0x00,
		0xfa, 0x1f, 0xba, 0xe4, 0x2b, 0x12, 0x85, 0xc0,
		0x35, 0x2f, 0x22, 0x75, 0x24, 0xbc, 0x9a, 0xb1,
		0x62, 0x54, 0x28, 0x8d, 0xd6, 0x86, 0x3d, 0xcc,
		0xd5, 0xb9, 0xf5, 0x4a, 0x1a, 0xd0, 0x54, 0x1b
	},
	(uint8_t []){
		0x00, 0x55, 0x7b, 0xe5, 0xe5, 0x84, 0xfd, 0x52,
		0xa4, 0x49, 0xb1, 0x6b, 0x02, 0x51, 0xd0, 0x5d,
		0x27, 0xf9, 0x4a, 0xb7, 0x6c, 0xba, 0xa6, 0xda,
		0x89, 0x0b, 0x59, 0xd8, 0xef, 0x1e, 0x15, 0x9d
	}
};

const uint8_t *message1_test[] =
{
	(uint8_t []){
		0x28, 0xfb, 0xc9, 0xba, 0xda, 0x03, 0x3b, 0x14,
		0x60, 0x64, 0x2b, 0xdc, 0xdd, 0xb9, 0x0c, 0x3f,
		0xb3, 0xe5, 0x6c, 0x49, 0x7c, 0xcd, 0x0f, 0x62,
		0xb8, 0xa2, 0xad, 0x49, 0x35, 0xe8, 0x5f, 0x03,
		0x76, 0x13, 0x96, 0x6d, 0xe4, 0xee, 0x00, 0x53,
		0x1a, 0xe6, 0x0f, 0x3b, 0x5a, 0x47, 0xf8, 0xda,
		0xe0, 0x69, 0x15, 0xd5, 0xf2, 0xf1, 0x94, 0x99,
		0x6f, 0xca, 0xbf, 0x26, 0x22, 0xe6, 0x88, 0x1e
	},
	(uint8_t []){
		0x50, 0x8f, 0x7e, 0x55, 0x3c, 0x06, 0x50, 0x1d,
		0x74, 0x9a, 0x66, 0xfc, 0x28, 0xc6, 0xca, 0xc0,
		0xb0, 0x05, 0x74, 0x6d, 0x97, 0x53, 0x7f, 0xa8,
		0x5d, 0x9e, 0x40, 0x90, 0x4e, 0xfe, 0xd2, 0x9d
	}
};

#endif