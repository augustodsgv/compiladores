#include <stdio.h>
#include <stdlib.h>
#include "file_read.h"

FILE * file;

char buffer[BUFFER_SIZE * 2];

int buffer_pos = 0;
int buffer_load_size = 0;    // Stores the amount of data loaded to the buffer
int buffer_regressed = 0;

/* File operations */

// Opens file to "file" var.
// Returns true if the file was opened successfully
int open_file(char * file_name){
    file = fopen(file_name, "r");
    return file != NULL;
}

// Returns if the program reached the end of the file
int reached_EOF(){
    return feof(file);
}

// Closes the file
void close_file(){
    fclose(file);
}

/* Buffer operations */
void start_buffer(){
    buffer_load_size = load_buffer(0);
}

// Reads data from file to the first (0) or the second (1) half
// Return the size in bytes that could be read
// If 0, means that no byte could be read
int load_buffer(int buffer_half){
    if (reached_EOF()){
        printf("Error: Trying to read file, but reached EOF\n");
        exit(1);
    }
    return fread(&buffer[BUFFER_SIZE * buffer_half], sizeof(char), BUFFER_SIZE, file);
}

// Returns if there are still tokens available for reading
int tokens_available(){
    // printf("buffer_pos %d\n", buffer_pos);
    if (!reached_EOF())     // Data in file
        return 1;

    // Data remaining in buffers
    if (buffer_pos < buffer_load_size - 1)      // Buffer 1 not empty
        return 1;

    if (buffer_pos >= BUFFER_SIZE && buffer_pos < BUFFER_SIZE + buffer_load_size - 1)    // Buffer 2 not empty
        return 1;

    return 0;
}

// Reads a char from buffer
char read_buffer(){
    char c_return = buffer[buffer_pos];
    increment_buffer();
    buffer_regressed = 0;
    return c_return;
}

// Increment buffer
void increment_buffer(){
    buffer_pos++;
    if(buffer_pos == BUFFER_SIZE){     // Reached end of first buffer
        if(!buffer_regressed)         // If buffer regressed, it should not load the buffer again
            buffer_load_size = load_buffer(1);
    }else if(buffer_pos == BUFFER_SIZE * 2){    // Reached end of second buffer
        if(!buffer_regressed)                        // If buffer regressed, it should not load the buffer again
            buffer_load_size = load_buffer(0);
        buffer_pos = 0;
    }
}

// Regress the buffer position
/* In case of tokens with more than one character, it
*  may be needed to check the next char but fall back.
*  In this case, we need to make sure that we do not 
*  reload the pre-fetched buffer.
*/
void regress_buffer(){
    if(buffer_pos == 0){
        buffer_regressed = 1;              // Marking that regressed to the previus buffer
        buffer_pos = BUFFER_SIZE * 2 - 1;  // Going to the last position of the second half buffer
    }else if (buffer_pos == BUFFER_SIZE){
        buffer_regressed = 1;
        buffer_pos = BUFFER_SIZE - 1;
    }else{
        buffer_pos--;
    }
}