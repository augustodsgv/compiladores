all: main

main: token file_read
	gcc main.c -o main -g3 token.o file_read.o

token:
	gcc token.c -c -g3

file_read:
	gcc file_read.c -c -g3