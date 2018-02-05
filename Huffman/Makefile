all: huffencode huffdecode

clean:
	-rm huffencode huffdecode

huffencode: huffman.h treeAndList.h huffman.c huffencode.c
	gcc -Wall -ansi -pedantic -g -o huffencode huffman.c huffencode.c

huffdecode: huffman.h treeAndList.h huffman.c huffdecode.c
	gcc -Wall -ansi -pedantic -g -o huffdecode huffman.c huffdecode.c


