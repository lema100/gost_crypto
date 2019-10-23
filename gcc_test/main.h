#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdint.h>

const uint8_t *mgm_key[] =
{
	(uint8_t []){
		0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
		0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
		0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
		0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF
	},
	(uint8_t []){
		0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88,
		0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
		0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
		0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
	}
};

const uint8_t *mgm_nonce[] =
{
	(uint8_t []){0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x00},
	(uint8_t []){0x12, 0xDE, 0xF0, 0x6B, 0x3C, 0x13, 0x0A, 0x59}
};

const uint8_t *mgm_p[] =
{
	(uint8_t []){
		0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x00,
		0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88,
		0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
		0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xEE, 0xFF, 0x0A,
		0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
		0x99, 0xAA, 0xBB, 0xCC, 0xEE, 0xFF, 0x0A, 0x00,
		0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
		0xAA, 0xBB, 0xCC, 0xEE, 0xFF, 0x0A, 0x00, 0x11,
		0xAA, 0xBB, 0xCC 
	},
	(uint8_t []){
		0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88,
		0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x00,
		0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xEE, 0xFF, 0x0A,
		0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
		0x99, 0xAA, 0xBB, 0xCC, 0xEE, 0xFF, 0x0A, 0x00,
		0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
		0xAA, 0xBB, 0xCC, 0xEE, 0xFF, 0x0A, 0x00, 0x11,
		0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
		0xAA, 0xBB, 0xCC
	}
};

const uint8_t *mgm_a[] =
{
	(uint8_t []){
		0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
		0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
		0xEA, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
		0x05 
	},
	(uint8_t []){
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
		0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
		0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
		0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
		0xEA
	}
};

const uint8_t *mgm_mic_test[] =
{
	(uint8_t []){
		0x8C, 0x9B, 0x22, 0x51, 0x29, 0x8A, 0x84, 0x93
	},
	(uint8_t []){
		0xA7, 0x92, 0x80, 0x69, 0xAA, 0x10, 0xFD, 0x10
	}
};

const uint8_t *mgm_test[] =
{
	(uint8_t []){
		0xEC, 0x0B, 0x4F, 0xBF, 0x55, 0x08, 0x8A, 0x5E,
		0x3E, 0x6C, 0x7E, 0x1D, 0x63, 0x63, 0x95, 0x3F,
		0x08, 0x59, 0xB8, 0xB2, 0x78, 0xF6, 0xFC, 0xCB,
		0x56, 0x6F, 0xAC, 0xC2, 0xB3, 0xC4, 0xE1, 0xAD,
		0x52, 0x99, 0x66, 0xCF, 0xA5, 0xBE, 0xEF, 0x09,
		0x74, 0xC8, 0xC5, 0xF7, 0x51, 0x9C, 0xF7, 0x41,
		0x64, 0x53, 0xB9, 0x06, 0xA5, 0xA1, 0x9A, 0x2C,
		0xB1, 0x66, 0xEB, 0xA1, 0x88, 0x2C, 0xD9, 0xE6,
		0xEC, 0xD7, 0x2F
	},
	(uint8_t []){
		0xC7, 0x95, 0x06, 0x6C, 0x5F, 0x9E, 0xA0, 0x3B,
		0x85, 0x11, 0x33, 0x42, 0x45, 0x91, 0x85, 0xAE,
		0x1F, 0x2E, 0x00, 0xD6, 0xBF, 0x2B, 0x78, 0x5D,
		0x94, 0x04, 0x70, 0xB8, 0xBB, 0x9C, 0x8E, 0x7D,
		0x9A, 0x5D, 0xD3, 0x73, 0x1F, 0x7D, 0xDC, 0x70,
		0xEC, 0x27, 0xCB, 0x0A, 0xCE, 0x6F, 0xA5, 0x76,
		0x70, 0xF6, 0x5C, 0x64, 0x6A, 0xBB, 0x75, 0xD5,
		0x47, 0xAA, 0x37, 0xC3, 0xBC, 0xB5, 0xC3, 0x4E,
		0x03, 0xBB, 0x9C
	}
};

const uint32_t mgm_p_size[] = {67, 67};
const uint32_t mgm_a_size[] = {41, 41};


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

const uint8_t data_ctr_iv[] = 
{
	0x12, 0x34, 0x56, 0x78, 0x00, 0x00, 0x00, 0x00
};

const uint8_t *data_ctr_test[] = 
{
	(uint8_t []){0x22, 0x9A, 0x5B, 0xFF, 0xDD, 0xF0, 0x81, 0x75},
	(uint8_t []){0x4e, 0x98, 0x11, 0x0c, 0x97, 0xb7, 0xb9, 0x3c},
	(uint8_t []){0x3e, 0x25, 0x0d, 0x93, 0xd6, 0xe8, 0x5d, 0x69},
	(uint8_t []){0x13, 0x6d, 0x86, 0x88, 0x07, 0xb2, 0xdb, 0xef},
	(uint8_t []){0x56, 0x8e, 0xb6, 0x80, 0xab, 0x52, 0xa1, 0x2d}
};


const uint8_t * mic_test[] = 
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
