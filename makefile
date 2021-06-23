CC=gcc
CFLAGS=-ansi -Wall

binary_tree: binary_tree.o
	$(CC) -o binary_tree binary_tree.o 