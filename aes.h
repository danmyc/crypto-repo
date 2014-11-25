#ifndef AES_H

#define AES_H

#include <iostream>
using namespace std;
#include <curses.h>
#include <stdio.h>
#include <string>



typedef unsigned char block[4][4];

void blockDisplay (block block);

void blockCopy (block to, block from);

void XOR (block op1, block op2, block &target);

void byteXOR (unsigned char op1, unsigned char op2, unsigned char &target);

int HEX2DEC (char ch);

char DEC2HEX (int n);

void HEX2BLOCK(block &block, char str[]);

void BLOCK2HEX(char str[], block block);

void blockDisplay (block block);



// class AES;

class AES {


private:

    block key[11];

    void keyExpansion (char k[]);

    void sBox (block &b);

    void sBoxInverse (block &b);

    void shiftRows (block &b);

    void shiftRowsInverse (block &b);

    void mixColumns (block &b);

    void mixColumnsInverse (block &b);


public:
    
    void encrypt (block &b, char k[]);

    void decrypt (block &b, char k[]);

}; // checked

extern AES aes;

#endif