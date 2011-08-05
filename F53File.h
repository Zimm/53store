#include <stdio.h>
#include <sys/stat.h>
#ifndef _F53File
#define _F53File

typedef struct bitHelper {
	unsigned b1 : 1;
	unsigned b2 : 1;
	unsigned b3 : 1;
	unsigned b4 : 1;
	unsigned b5 : 1;
	unsigned b6 : 1;
	unsigned b7 : 1;
	unsigned b8 : 1;
};

class F53File {
        	char *_file;
		struct stat fileStat;
	public:
                F53File(char *file);
                uint6_t *getData(int *length);
                void writeData(uint6_t *data, int length);
		static uint8_t *getCharFromData(uint6_t *data, int asdf);
		static uint6_t *getDataFromChar(char*c);
};

#endif

