#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "F53Encoder.h"
#include "F53Decoder.h"
#include "F53File.h"

using namespace std;

void createData(bool fromFile, int argc, char **argv) {
	int hasOut = -1;

	for (int i = 0; i < argc; i++) {
		
		if (strlen(argv[i]) == 2 && !strcmp(argv[i], "-o")) {
			hasOut = i;
			break;
		}
	}
	//Get output

	char *input;

	if (fromFile) {
		
		struct stat st;

		if (stat(argv[2], &st) != 0) {
			cout << "Unable to open file " << argv[2] << endl;
			exit(-1);
		}

		//check its there

		FILE *pFile = fopen(argv[2], "r");
		
		input = (char *)calloc(st.st_size+1,sizeof(char));

		fread(input, 1, st.st_size, pFile);
	
		fclose(pFile);

	} else {

		input = (char *)calloc(strlen(argv[2])+1,sizeof(char));
		strcpy(input, argv[2]);
		
	}


	F53Encoder encoder;

	int length = 0;

	uint6_t *digits = encoder.encodeStatement(input, &length);

	if (hasOut == -1) {
		//print to the console or w.e
		for (int i = 0; i < length; i++) {

         	       cout << digits[i].b1 << digits[i].b2 << digits[i].b3 << digits[i].b4 << digits[i].b5 << digits[i].b6;

        	}

		cout << endl;

	} else {
		
		FILE *pFile = fopen(argv[hasOut+1], "w+");
		
		fclose(pFile);

		F53File file((char *)argv[hasOut+1]);

		file.writeData(digits, length);
		
	}

	delete digits;

}

void extractData(bool afile, int argc, char **argv) {

	cout << "Ooops not implemented yet" << endl;

}

void printHelp() {

	cout << "need to put in help, note to self" << endl;

}

int main(int argc, char **argv) {
	
	int args = argc - 1; //just easier to think about when coding

	if (args <= 0) {
		printHelp();
		exit(-1);
	}
	
	string firstFlag = argv[1];
	if (argv[1][0] == '-')
		firstFlag = firstFlag.substr(1,firstFlag.length()-1);

	switch (firstFlag.c_str()[0]) {
		case 'c':
			createData(firstFlag.c_str()[1] == 'f', argc, argv);
			break;
		case 'x':
			extractData(firstFlag.c_str()[1] == 'f', argc, argv);
			break;
		default:
			printHelp();
			exit(-1);
			break;
	}

	return 0;
}
		
		
	
