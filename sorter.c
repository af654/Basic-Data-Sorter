#include <stdio.h>
#include <string.h>
#include "Sorter.h"
#include "mergesort.c"

#define MAX_NUM_ROWS 8192
#define MAX_NUM_COL 30

//array to hold the rows read in from stdin -> im not sure if we need an array here 
Row rows[MAX_NUM_ROWS];
//store types 
char types[MAX_NUM_COLS];
//point_to_row is a an array of pointers 
Row* point_to_row[MAX_NUM_ROWS];

int main(int argc, char* argv[]) {

	if ( argc != 3 || strcmp(argv[1],"-c") != 0) {
        printf("The command line must follow the following format:\ncat input.file | ./sorter -c  movie_title");
    } else if (!isValidColumn(argv[2])) {
        printf("%s is not a valid column type. Please consult documentation for list of proper columns.",argv[2]);
    } else {
        //Loop through STDIN and use the implemented getline() to get the whole line to put into an allocated row struct.
        //while not at the end of the file (might not know how many rows you have)
        while(!feof(stdin)){ 
            int i = 0;
            char *line = NULL;
            char *value;        
            const char s[1] = ",";
            size_t size;

            //GET DATA
            getline(&line, &size, stdin);        

            //if first line put into type array
            if(i==0){
                //Uses the stdlib strtok function which splits up the string based on a character.
                //Because it is a CSV file we split between the commas
                //PARSE DATA AND STORE DATA
                value = strtok(line, s);
                //put types in type array
                types[0]=malloc(strlen(value) + 1);
                strcpy(types[0], value);
                /* walk through other values */
                //don't use \n because that gives them into new lines 
                int j = 1;
                while( value != NULL ) {
                    printf( "%s", value );
                    value = strtok(NULL, s);
                    types[j] = malloc(strlen(value) + 1);
                    strcpy(types[j], value);
                    j++;
                }
                i++;
            //the rest of the rows you have to store differently
            } else {
                //implementation: for each row malloc for 30 column structs 
                //malloc for 30 column structs ie allocating space for data
                //malloc returns a pointer to some allocated memory and we have to populate it 
                //I DONT KNOW IF IM DOING THIS RIGHT AHHHHHHHHH
                rows[i] = (char*)malloc(MAX_NUM_COL*sizeof(char *));
                //a pointer pointing to the front of this line which is allocated for 30 columns
                //ie storing the starting address of the row to the pointer variable firstdata
                point_to_row[i] = &rows[i]; 
                //firstdata[0] points to the first string in the row of the 2-D array
                //PARSE DATA AND STORE EACH DATA 
                rows[i].color = malloc(strlen(value) + 1);
                strcpy(rows[i].color, value);

                rows[i].directorName = malloc(strlen(value)+1);
                strcpy(rows[i].directorName, value);

                rows[i].numCriticForReview = malloc(strlen(value)+1);
                strcpy(rows[i].numCriticForReview, value);
                
                rows[i].duration = malloc(strlen(value)+1);
                strcpy(rows[i].duration,value);

                rows[i].directorFacebookLikes = malloc(strlen(value)+1);
                strcpy(rows[i].directorFacebookLikes,value);

                //do this for all values
                //do we need to realloc for more space in the rows array? Because right now it is constantrrr
            }
        }//end of while

        //mergesort(array that holds data for the input column) and spits out order to move the rows
        //sort rows by pointers pointing to each row
        //print out types array
        //print out rows sorted

    }//end of else
} //end of main

//const array is put in the header file, input string is compared against names found there.
//returns 1 if the input  is a valid column that can be searched, 0 otherwise
int isValidColumn(char* columnName) {
    for(int i = 0; i < (sizeof(validColumns) / sizeof(validColumns[i])); i++){
        if(strcmp(validColumns[i], columnName) == 0) {
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
