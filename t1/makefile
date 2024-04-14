all: main

main: token file_read language
	gcc main.c -o main -g3 language.o token.o file_read.o
	rm language.o token.o file_read.o

language: token file_read
	gcc language.c -c -g3

token:
	gcc token.c -c -g3

file_read:
	gcc file_read.c -c -g3

teste_buffer: file_read
	gcc teste_buffer.c file_read.o -o teste_buffer