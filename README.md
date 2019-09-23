# GOST crypto
Lightweight GOST crypto GCC/STM32

Part implementation of GOST crypto algorithm  
GOST 34.11-2012 HASH 256/512 "Stribog"  
GOST 34.12-2015 Block encryption/decryption method "Magma"  
GOST 34.13-2015 ECB and MIC method of "Magma"  

Atolic True Studio 9.2.0  
Performance tests  
MCU configuration STM32L071KB (Cortex M0+) tacted from HSI 16MHz  

| Magma									|	Os		|	O3		|	O2	 	|	O1		|	O0		|
|---------------------------------------|-----------|-----------|-----------|-----------|-----------|
| ROM									|	848B	|	2.36kB	|	1.27kB	|	1016B	|	2.06kB	|
| RAM per ctx							|	184B	|	184B	|	184B	|	184B	|	184B	|
| Encrypt 1000 blocks, ms				|	1012	|	360		|	1022	|	1011	|	2895	|
| Decrypt 1000 blocks, ms				|	1012	|	360		|	1022	|	1011	|	2896	|
| MIC calc for 4 blocks 1000 times, ms	|	4011	|	1408	|	4054	|	4013	|	11583	|
| MIC calc for 2 blocks 1000 times, ms	|	2016	|	712		|	2036	|	2016	|	5810	|

| Stribog								|	Os		|	O3		|	O2	 	|	O1		|	O0		|
|---------------------------------------|-----------|-----------|-----------|-----------|-----------|  
| ROM									|	2.36kB	|	5.12kB	|	2.55kB	|	2.43kB	|	3.16kB  |
| RAM per ctx							|	193B	|	193B	|	193B	|	193B	|	193B	| 
| HASH 512 for 63 byte 100 times, ms	|	6631	|	2720	|	5013	|	5119	|	19122	|
| HASH 256 for 63 byte 100 times, ms	|	6618	|	2714	|	5008	|	5112	|	19000	|
| HASH 512 for 72 byte 100 times, ms	|	8825	|	3623	|	6683	|	6822	|	25493	|
| HASH 256 for 72 byte 100 times, ms	|	8820	|	3618	|	6680	|	6818	|	25400	|
| HASH 512 for 32 byte 100 times, ms	|	6624	|	2713	|	5007	|	5113	|	19102	|
| HASH 256 for 32 byte 100 times, ms	|	6637	|	2717	|	5010	|	5118	|	19100	|

