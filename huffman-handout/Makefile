CC=gcc -std=c99 -pedantic
CFLAGS=-Wall -Wextra -Werror -Wshadow -fsanitize=undefined -g

LIB=lib/*.o
SAFE_LIB=$(LIB:%.o=%-safe.o)
FAST_LIB=$(LIB:%.o=%-fast.o)

GIVEN1=freqtable.o htree.o encode.o bitpacking.o compress.o main.o
SAFE1=$(GIVEN1:%.o=%-safe.o)
FAST1=$(GIVEN1:%.o=%-fast.o)

GIVEN2=freqtable.o htree.o bitpacking.o test-htree.c
SAFE2=$(GIVEN2:%.o=%-safe.o)

GIVEN3=freqtable.o htree.o bitpacking.o test-pack.c
SAFE3=$(GIVEN3:%.o=%-safe.o)

safe:
	$(CC) $(CFLAGS) -DDEBUG $(SAFE_LIB) $(SAFE1) huffman.c \
	    -o huff-safe

fast:
	$(CC) $(CFLAGS) $(FAST_LIB) $(FAST1) huffman.c \
	     -o huff-fast

htree:
	$(CC) $(CFLAGS) -DDEBUG $(SAFE_LIB) $(SAFE2) huffman.c \
	     -o test-htree

pack:
	$(CC) $(CFLAGS) -DDEBUG $(SAFE_LIB) $(SAFE3) huffman.c \
	     -o test-pack
