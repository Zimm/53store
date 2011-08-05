
class F53Decoder {
        public:
                char decodeChar(uint6_t c);
                char decodeSpecial(uint6_t c);
                char *decodeStatement(uint6_t *c, int length);
};

