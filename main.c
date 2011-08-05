#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "F53Encoder.h"

using namespace std;

int main(int argc, char **argv) {

	char *word = argc > 1 ? argv[1] : (char*)"poop";
	
	cout << word << endl;

	F53Encoder encoder;

	uint6_t *digits = encoder.encodeStatement(word);

	for (int i = 0; i < strlen(word); i++) {

		cout << digits[i].b1 << digits[i].b2 << digits[i].b3 << digits[i].b4 << digits[i].b5 << digits[i].b6 << endl;

	}

	return 0;
}
