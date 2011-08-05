#include <fstream>
#include <iterator>
#include "F53Encoder.h"
#include "F53File.h"
#include <sys/stat.h>
#include <iostream>

using namespace std;


F53File::F53File(char *file) {

	if (stat(file, &fileStat) != 0) {

		cout << file << " does not exist" << endl;
	}

	_file = (char *)calloc(strlen(file)+1, sizeof(char));

	strcpy(_file, file);

}


uint6_t *F53File::getData(int *length) {


	


}

uint8_t *F53File::getCharFromData(uint6_t *data, int offset) {

	uint8_t *byte = (uint8_t *)calloc(3, sizeof(uint8_t));

	byte[0] = (data[offset].b1) | (data[offset].b2 << 1) | (data[offset].b3 << 2) | (data[offset].b4 << 3) | (data[offset].b5 << 4) | (data[offset].b6 << 5) | (data[offset+1].b1 << 6) | (data[offset+1].b2 << 7);
	byte[1] = (data[offset+1].b3) | (data[offset+1].b4 << 1) | (data[offset+1].b5 << 2) | (data[offset+1].b6 << 3) | (data[offset+2].b1 << 4) | (data[offset+2].b2 << 5) | (data[offset+2].b3 << 6) | (data[offset+2].b4 << 7);

	byte[2] = (data[offset+2].b5) | (data[offset+2].b6 << 1) | (data[offset+3].b1 << 2) | (data[offset+3].b2 << 3) | (data[offset+3].b3 << 4) | (data[offset+3].b4 << 5) | (data[offset+3].b5 << 6) | (data[offset+3].b6 << 7);

	cout << (byte[0]) << endl << byte[1] << endl << byte[2] << endl;

	return byte;

}

void F53File::writeData(uint6_t *data, int length) {

	FILE * pFile;

	pFile = fopen ( _file , "wb" );

	int left = length % 4;
	
	length -= left;

	for (int i = 0; i < (length/4 +(left>0?1:0)); i++) {
		uint8_t *tmp = getCharFromData(data, i*4);
		cout << tmp[0] << endl << tmp[1] << endl << tmp[2] << endl;
		fwrite(tmp, 1, sizeof(uint8_t)*3, pFile);
		free(tmp);
	}

	fwrite((void *)&left, 1, sizeof(uint8_t), pFile);

	fclose(pFile);

}

