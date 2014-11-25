#ifndef CBC_H

#define CBC_H

#include <iostream>
using namespace std;
#include <curses.h>
#include <stdio.h>
#include <cstring>

#include "aes.h"



void extract (char to[], char from[], int num);

void insert (char from[], char to[], int num);


class CBC {


public:

    void encrypt (char c[], char m[], char IV[], char k[]);

    void decrypt (char m[], char c[], char k[]);

};

extern CBC cbc;

#endif