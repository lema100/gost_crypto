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
| ROM, byte								|	828		|	2.33k	|	1.3k	|	1016	|	2.01k	|
| RAM per ctx, byte						|	56		|	56		|	56		|	56		|	56		|
| Encrypt 1000 blocks, ms				|	1028	|	388		|	1036	|	1026	|	2976	|
| Decrypt 1000 blocks, ms				|	1031	|	407		|	1040	|	1027	|	2976	|
| MIC calc for 4 blocks 1000 times, ms	|	4073	|	1521	|	4111	|	4075	|	11906	|
| MIC calc for 2 blocks 1000 times, ms	|	2046	|	769		|	2065	|	2048	|	5970	|

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

