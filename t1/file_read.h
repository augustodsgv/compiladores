#ifndef FILE_READ_H
#define FILE_READ_H

#define BUFFER_SIZE 10

/* File operations */
int open_input_file(char * file_name);
int open_ouput_file(char * file_name);
int reached_EOF();
void closefile();

/* Buffer operations */
void start_buffer();
int load_buffer();
int tokens_available();
char read_buffer();
void increment_buffer();
void regress_buffer();
void print_buffer();

#endif /* FILE_READ_H */