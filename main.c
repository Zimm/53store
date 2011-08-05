#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "F53Encoder.h"
#include "F53Decoder.h"

using namespace std;

int main(int argc, char **argv) {

	char *word = argc > 1 ? argv[1] : (char*)"poop";
	
	cout << word << endl;

	F53Encoder encoder;

	int length = 0;

	uint6_t *digits = encoder.encodeStatement(word, &length);

	for (int i = 0; i < length; i++) {

		cout << digits[i].b1 << digits[i].b2 << digits[i].b3 << digits[i].b4 << digits[i].b5 << digits[i].b6 << endl;

	}

	F53Decoder decoder;

	char *result = decoder.decodeStatement(digits, length);

	cout << "decoded: " << result << endl;

	return 0;
}
