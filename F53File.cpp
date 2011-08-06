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

uint6_t *F53File::getDataFromChar(char *c) {

	size_t length = strlen(c);

	if (length != 3)
		return NULL;

	uint6_t *result = (uint6_t *)calloc(4, sizeof(uint6_t));

	result[0] = F53Encoder::condense((c[0] & magicCondesner));

	uint8_t tmp = c[0] & 0xC0;

	tmp >>= 6;

	uint8_t tmp1 = c[1] & 0x0F;

	tmp1 <<= 2;

	uint6_t asdf = F53Encoder::condense((tmp | tmp1));

	result[1] = F53Encoder::condense((tmp | tmp1));

	tmp = c[1] & 0xF0;

	tmp >>= 4;

	tmp1 = c[2] & 0x3;

	tmp1 <<= 4;

	result[2] = F53Encoder::condense((tmp | tmp1));

	tmp = c[2] & 0xFC;

	tmp >>= 2;

	result[3] = F53Encoder::condense(tmp);

	return result;

}


uint6_t *F53File::getData(int *length) {
	
	int alength;

	unsigned char *data;
	
	if (fileStat.st_size > 0) {

		FILE *pFile;
		
		pFile = fopen(_file, "r");
		
		data = new unsigned char[fileStat.st_size];
		
		fread(data, 1, fileStat.st_size, pFile);
		
		fclose(pFile);

		alength = fileStat.st_size;

	} else {

		return NULL;

		data = new unsigned char[strlen(_file)];

		strcpy((char *)data,_file);

		alength = strlen(_file);

	}	
	
	uint8_t leftOver = (uint8_t)data[alength-1];

	int over = (int)leftOver;

	uint6_t *result = (uint6_t *)calloc(4*((alength - over -1)/3 + over), sizeof(uint6_t));

	int place, where = 0;

	for (int i = 0; i < ((alength - over -1)/3); i++) {

		char *tmp = new char[3];
		
		tmp[0] = data[i*3];
		tmp[1] = data[(i*3)+1];
		tmp[2] = data[(i*3)+2];

		place = (i*3)+2;

		uint6_t *tmp1 = getDataFromChar(tmp);

		delete tmp;

		result[i*4] = tmp1[0];
		result[(i*4)+1] = tmp1[1];
		result[(i*4)+2] = tmp1[2];
		result[(i*4)+3] = tmp1[3];

		where = (i*4)+3;

		delete tmp1;

	}

	char *tmp = new char[3];

	for (int a = 0; a < 3; a++) {
		tmp[a] = data[++place];
	}

	for (int a = 0; a < over; a++) {
		uint6_t thing = F53Encoder::condense(0);
		switch (a) {
			case 0:
				thing = F53Encoder::condense((tmp[0] & magicCondesner));
				break;
			case 1:
				thing = F53Encoder::condense((((((uint8_t)tmp[0]) >> 6) & 0x3) | ((((uint8_t)tmp[1]) << 2) & 0x3C)));
				break;
			case 2:
				thing = F53Encoder::condense((((((uint8_t)tmp[1]) >> 4) & 0xF) | ((((uint8_t)tmp[1]) << 4) & 0x30)));
				break;
			default:
				cout << "Ooops..." << endl;
				break;
		}
		result[++where] = thing;
	}

	*length = 4*((alength -1)/3) + over;

	return result;
	
}

uint8_t *F53File::getCharFromData(uint6_t *data, int offset) {

	uint8_t *byte = (uint8_t *)calloc(3, sizeof(uint8_t));

	byte[0] = (data[offset].b1) | (data[offset].b2 << 1) | (data[offset].b3 << 2) | (data[offset].b4 << 3) | (data[offset].b5 << 4) | (data[offset].b6 << 5) | (data[offset+1].b1 << 6) | (data[offset+1].b2 << 7);
	byte[1] = (data[offset+1].b3) | (data[offset+1].b4 << 1) | (data[offset+1].b5 << 2) | (data[offset+1].b6 << 3) | (data[offset+2].b1 << 4) | (data[offset+2].b2 << 5) | (data[offset+2].b3 << 6) | (data[offset+2].b4 << 7);

	byte[2] = (data[offset+2].b5) | (data[offset+2].b6 << 1) | (data[offset+3].b1 << 2) | (data[offset+3].b2 << 3) | (data[offset+3].b3 << 4) | (data[offset+3].b4 << 5) | (data[offset+3].b5 << 6) | (data[offset+3].b6 << 7);


	return byte;

}

void F53File::writeData(uint6_t *data, int length) {

	FILE * pFile;

	pFile = fopen ( _file , "w+" );

	int left = length % 4;
	
	length -= left;

	for (int i = 0; i < (length/4 +(left>0?1:0)); i++) {
		uint8_t *tmp = getCharFromData(data, i*4);
		fwrite(tmp, 1, sizeof(uint8_t)*3, pFile);
		free(tmp);
	}

	fwrite((void *)&left, 1, sizeof(uint8_t), pFile);

	fclose(pFile);

}

