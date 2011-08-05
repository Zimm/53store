all:lib53Store

test:
	@echo 'Building test program....'
	@g++ main.cpp -o build/test build/lib53Store.a

lib53Store:F53Encoder.cpp F53Decoder.cpp F53File.cpp
	@mkdir -p build/
	@echo 'Building library....'
	@g++ -dynamiclib $? -o build/lib53Store.a
#	@ar -rs build/lib53Store.a *.o
clean:
	rm -rf build/
