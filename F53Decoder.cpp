#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "F53Encoder.h"
#include "F53Decoder.h"

using namespace std;

char F53Decoder::decodeChar(uint6_t c) {

	for (int i = 0; i < encoderTableLength; i++) {

		if (F53Encoder::makeDense(c) == i) {
			return encoderTable[i];
		}
	}

	return -1;
}

char F53Decoder::decodeSpecial(uint6_t c) {

	c = F53Encoder::condense(F53Encoder::makeDense(c)+54);

	return decodeChar(c);

}

char *F53Decoder::decodeStatement(uint6_t *c, int length) {

	char *result = (char *)calloc(length, sizeof(char));

	int where = 0;

	for (int i = 0; i < length; i++) {

		char tmp = decodeChar(c[i]);

		if (tmp == (char)-128) {

			result = (char *)realloc(result, length - 1*sizeof(char));
		
			result[where] =	decodeSpecial(c[++i]);

		} else {
			result[where] = tmp;
		}

		where++;	

	}	

	result[where] = '\0';

	return result;

}

