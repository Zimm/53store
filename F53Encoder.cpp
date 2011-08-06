#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "F53Encoder.h"

using namespace std;


const char encoderTable[100] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', (char)-128, '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\n', '\r', '.', ',', '"', '\'', '/', '\\', '!', '?', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-','_', ';', ':', '=', '+', '[',']','{', '}','<','>','`','~', '\t','|','\0'};

const unsigned int encoderTableLength = 100;

const int magicCondesner = 0x3F; // value of 0b00111111 so theres only 6 bits left, yayz

uint6_t F53Encoder::condense(int i) {
	
	uint6_t result = *(uint6_t *)&i;

	return result;

}


int F53Encoder::makeDense(uint6_t i) {
	return *(int *)&i;
}

uint6_t F53Encoder::encodeChar(char c) {

	for (int i = 0; i <= 26; i++) {

		if (c == encoderTable[i])
			return condense(i);

	}

	for (int i = 27; i < 52; i++) {

		if (c == encoderTable[i])
			return condense(i);

	}

	for (int i = 54; i < encoderTableLength; i++) {
		if (c == encoderTable[i])
			return condense(magicCondesner-1);	
	}

	return condense(magicCondesner);

//i think this will work.... cuz of spill over, not sure, works with int to char so hopefully this works with two bits less
}

uint6_t *F53Encoder::encodeSpecial(char c) {

	uint6_t test = encodeChar(c);

	uint6_t *result = (uint6_t *)calloc(2, sizeof(uint6_t));

	if (makeDense(test) != magicCondesner-1) {

		result[0] = test;

		return result;
	}

	result[0] = condense(53);

	for (int i = 54; i < encoderTableLength; i++) {
                if (c == encoderTable[i])
			result[1] = condense(i-54);
        }

	return result;
}

uint6_t *F53Encoder::encodeStatement(char *c, int *alength) {

	size_t length = strlen(c);

	uint6_t *result = (uint6_t *)calloc(length, sizeof(uint6_t));
	
	int where = 0;

	for (int i=0; i < strlen(c); i++) {
		uint6_t tmp = encodeChar(c[i]);
		if (makeDense(tmp) == magicCondesner-1) {
			length++;
			result = (uint6_t *)realloc(result, length*sizeof(uint6_t));
			
			uint6_t *tmpS = encodeSpecial(c[i]);

			result[where] = tmpS[0];
			result[++where] = tmpS[1];
			
			free(tmpS);

		} else {

			result[where] = tmp;

		}
		
		where++;
	}

	*alength = length;

	return result;

	//note you are in charge of freeing this, yes sorry no fancy schmancy c++ class for one of these 6 bit ints....
}

