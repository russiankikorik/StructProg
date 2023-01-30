sources=$(shell ls ./*.c)

.PHONEY: all debug clean

all:
		gcc -o compressor $(sources)

debug:
		gcc -g -o compressor $(sources)
clean:
		rm -rf compressor


