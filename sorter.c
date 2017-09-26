#include <stdio.h>
#include <string.h>
#include "Sorter.h"
#include "mergesort.c"

#define MAX_NUM_ROWS 8192

int main(int argc, char* argv[]) {
    //array to hold the rows read in from stdin
    struct row rows[MAX_NUM_ROWS];

	if ( argc != 3 
        || strcmp(argv[1],"-c") != 0) {
        printf("The command line must follow the following format:\ncat input.file | ./sorter -c  movie_title");
    } else if (!isValidColumn(argv[2])) {
        printf("%s is not a valid column type. Please consult documentation for list of proper columns.",argv[2]);
    }

    //Loop through STDIN and use the implemented getline() to get the whole line to put into an allocated row struct.
    for(int i = 0; i < 10; i++) { //change from 5 to valid once fully implmented
        char *line = NULL;
        char *token;        
        const char s[1] = ",";
        size_t size;

        getline(&line, &size, stdin);        
        //Uses the stdlib strtok function which splits up the string based on an character.
        //Becuase it is a CSV file we split between the commas
        token = strtok(line, s);
        
        /* walk through other tokens */
        while( token != NULL ) {
            printf( "%s\n", token );
            token = strtok(NULL, s);
        }
    }
} //end of main

//const array is put in the header file, input string is compared against names found there.
//returns 1 if the input  is a valid column that can be searched, 0 otherwise
int isValidColumn(char* columnName) {
    for(int i = 0; i < (sizeof(validColums) / sizeof(validColums[i])); i++){
        if(strcmp(validColums[i], columnName) == 0) {
            return 1;
        }
    }
    return 0;
}

//getline is a POSIX function, however on windows machines this is not availible. Below is an implementation of get line which return the line.
size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}
