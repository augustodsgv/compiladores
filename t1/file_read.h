/*
    Description: File and buffer description for read data from files
    Authors: Augusto dos Santos and Gabriel Nadalin
    Date: April 2024
*/
#ifndef FILE_READ_H
#define FILE_READ_H

#define BUFFER_SIZE 10

/* File operations */
int open_input_file(char * file_name);
int reached_EOF();
void close_input_file();

/* Buffer operations */
void start_buffer();
int load_buffer();
char read_buffer();
void increment_buffer();
void regress_buffer();
void print_buffer();

#endif /* FILE_READ_H */