all:lib53Store

test:lib53Store
	@echo 'Building test program....'
	@g++ main.c -o build/test build/lib53Store.a

lib53Store:F53Encoder.cpp F53Decoder.cpp
	@mkdir -p build/
	@echo 'Building library....'
	@g++ -dynamiclib $? -o build/lib53Store.a
#	@ar -rs build/lib53Store.a *.o
clean:
	rm -rf build/
