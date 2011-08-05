#include <stdio.h>

#ifndef _F53Encoder
#define _F53Encoder

typedef struct uint6_t {
        unsigned b1 : 1;
        unsigned b2 : 1;
        unsigned b3 : 1;
        unsigned b4 : 1;
        unsigned b5 : 1;
        unsigned b6 : 1;
};

//so it turns out a class cant start with a number?
extern const char encoderTable[65];
extern const unsigned int encoderTableLength;
extern const int magicCondesner;

static uint6_t condense(int i);

class F53Encoder {
                //Have to change readme;
        public:
                uint6_t encodeChar(char c);
                uint6_t *encodeStatement(char *c);
};


#endif

