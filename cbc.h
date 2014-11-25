
#include<iostream>
using namespace std;
#include<conio.h>
#include<stdio.h>
#include<string>

#include "aes.h"







void extract (char to[], char from[], int num) {
	for (int i = 0; i<32; i++) {
		to[i] = from[num*32 + i];
	}
}

void insert (char from[], char to[], int num) {
	for (int i = 0; i<32; i++) {
		to[num*32 + i] = from[i];
	}
}




class cbc {



public:


	void encrypt (char c[], char m[], char IV[], char k[]) {

		int string_length = strlen(m),
			num_blocks = string_length/32 + 1,
			padding = (32 - (string_length % 32))/2,
			i;
		block block,
			add;
		char block_hex[32];

		for (int j = string_length; j<(num_blocks * 32); j++) {
			m[j] = HEX2DEC(padding/16);
			m[j+1] = HEX2DEC(padding%16);
			j+=2;
		}
			
		insert(IV, c, 0);
		HEX2BLOCK (add, IV);
		
		for (i = 0; i < (num_blocks); i++) {

			extract (block_hex, m, i);
			HEX2BLOCK (block, block_hex);

			XOR(block, add, block);
			aes.encrypt(block, k);
			BLOCK2HEX (block_hex, block);

			insert (block_hex, c, i+1);
			blockCopy (add, block);
		}

		c[num_blocks * 32] = '\0';
		
	}



	void decrypt (char m[], char c[], char k[]) {

		int string_length = strlen(c),
			num_blocks = string_length/32 - 1,
			padding,
			i;
		block block, add;
		char add_hex[32], block_hex[32];

		extract (add_hex, c, 0);
		HEX2BLOCK (add, add_hex);

		for (i = 1; i<=num_blocks; i++) {

			extract (block_hex, c, i);
			HEX2BLOCK (block, block_hex);

			aes.decrypt (block, k);

			XOR (block, add, block);
			HEX2BLOCK (add, block_hex);

			BLOCK2HEX (block_hex, block);
			insert (block_hex, m, i-1);
		}

		padding = HEX2DEC (m[num_blocks*32 - 2]) * 16;
		padding += HEX2DEC (m[num_blocks*32 - 1]);

		m[num_blocks*32 - padding*2] = '\0';

	}


} cbc;



