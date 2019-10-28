# GOST crypto
Lightweight GOST crypto GCC/STM32

Part implementation of GOST crypto algorithm  
GOST 34.11-2012 HASH 256/512 "Stribog"  
GOST 34.12-2015 Block encryption/decryption method "Magma"  
GOST 34.13-2015 CTR, ECB and MIC method of "Magma"  

Atolic True Studio 9.2.0  
Performance tests  
MCU configuration STM32L071KB (Cortex M0+) tacted from HSI 16MHz  

| Magma									|	Os		|	O3		|	O2	 	|	O1		|	O0		|
|---------------------------------------|-----------|-----------|-----------|-----------|-----------|
| ROM, byte								|	952		|	2.6k	|	1.47k	|	1.17k	|	2.41k	|
| RAM per ctx, byte						|	56		|	56		|	56		|	56		|	56		|
| CTR encrypt 4 blocks 1000 blocks, ms	|	4157	|	1588	|	4192	|	4153	|	12099	|
| CTR decrypt 4 blocks 1000 blocks, ms	|	4157	|	1589	|	4192	|	4152	|	12099	|
| CTR encrypt 1 blocks 1000 blocks, ms	|	1047	|	413		|	1058	|	1048	|	3022	|
| CTR decrypt 1 blocks 1000 blocks, ms	|	1046	|	413		|	1059	|	1048	|	3022	|
| ECB encrypt 1000 blocks, ms			|	1028	|	388		|	1036	|	1026	|	2976	|
| ECB decrypt 1000 blocks, ms			|	1031	|	407		|	1040	|	1027	|	2976	|
| MIC calc for 4 blocks 1000 times, ms	|	4073	|	1521	|	4111	|	4075	|	11906	|
| MIC calc for 2 blocks 1000 times, ms	|	2046	|	769		|	2065	|	2048	|	5970	|

| Magma MGM								|	Os		|	O3		|	O2	 	|	O1		|	O0		|
|---------------------------------------|-----------|-----------|-----------|-----------|-----------|
| ROM magma, byte						|	656		|	1.37k	|	1.06k	|	780		|	1.63k	|
| ROM mgm, byte							|	780		|	1.68k	|	1.02k	|	920		|	1.88k	|
| RAM per ctx, byte						|	56		|	56		|	56		|	56		|	56		|
| Encrypt 2 blocks 1000 blocks, ms		|	3074	|	1162	|	3105	|	3075	|	8929	|
| Decrypt 2 blocks 1000 blocks, ms		|	3075	|	1161	|	3106	|	3075	|	8930	|
| MIC 2 blocks 1000 times, ms			|	18257	|	7542	|	13116	|	13579	|	42128	|

| Stribog								|	Os		|	O3		|	O2	 	|	O1		|	O0		|
|---------------------------------------|-----------|-----------|-----------|-----------|-----------|  
| ROM, byte								|	2.23k	|	4.98k	|	2.41k	|	2.3k	|	3.02k	|
| RAM per ctx, byte						|	193		|	193		|	193		|	193		|	193		| 
| HASH 512 for 63 byte 100 times, ms	|	6631	|	2720	|	5013	|	5119	|	19122	|
| HASH 256 for 63 byte 100 times, ms	|	6618	|	2714	|	5008	|	5112	|	19000	|
| HASH 512 for 72 byte 100 times, ms	|	8825	|	3623	|	6683	|	6822	|	25493	|
| HASH 256 for 72 byte 100 times, ms	|	8820	|	3618	|	6680	|	6818	|	25400	|
| HASH 512 for 32 byte 100 times, ms	|	6624	|	2713	|	5007	|	5113	|	19102	|
| HASH 256 for 32 byte 100 times, ms	|	6637	|	2717	|	5010	|	5118	|	19100	|

