#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "F53Encoder.h"
#include "F53Decoder.h"
#include "F53File.h"

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

	delete result;

	F53File file((char *)"test.53store");

	file.writeData(digits, length);

	delete digits;

	F53File reader((char *)"test.53store");

	uint6_t *adigits = reader.getData(&length);

	for (int i = 0; i < length; i++) {

                cout << adigits[i].b1 << adigits[i].b2 << adigits[i].b3 << adigits[i].b4 << adigits[i].b5 << adigits[i].b6 << endl;

        }
	
	char *aresult = decoder.decodeStatement(adigits, length);
	
	cout << "decoded from reading: " << aresult << endl;

	delete aresult;

	return 0;
}
