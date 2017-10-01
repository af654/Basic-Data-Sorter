#include <stdio.h>
#include <string.h>
#include "Sorter.h"
#include "mergesort.c"

#define MAX_NUM_ROWS 8192
#define MAX_NUM_COLS 64

int main(int argc, char* argv[]) {
    //2D array of structs
    Row *rows[MAX_NUM_ROWS];
    int row_number = 0;   
    char* column_to_sort; 
    int column_number_to_sort; 

    if ( argc != 3 || strcmp(argv[1],"-c") != 0) {
        printf("The command line must follow the following format:\ncat input.file | ./sorter -c  movie_title");
        return 0;
    } else if (!isValidColumn(argv[2])) {
        printf("%s is not a valid column type. Please consult documentation for list of proper columns.",argv[2]);
        return 0;
    }

    column_to_sort = argv[2];
    //search function on validcolumns
    int num;
    for(num = 0; num < (sizeof(validColumns) / sizeof(validColumns[num])); num++){
        if(strcmp(validColumns[num], column_to_sort) == 0) {
            column_number_to_sort = num;
            break;
        }
    }

    //Loop through STDIN and use the implemented parseline() to get the whole line to put into an allocated row struct.
    while(!feof(stdin)) {
        char* line = NULL;
        const char s[1] = ",";
        char* value;  
        char* token;
        char* current_row_values[MAX_NUM_COLS];
        size_t size;
        
        int value_index = 0;
        parseline(&line, &size, stdin);  
        token = strtok_single(line, s);

        //Walk through other tokens on the line
        while(token) {
            //If the value we are reading in is Null, we want to replace it with the string "<EMPTY>"
            value = *token ? token : "<EMPTY>";
            
            //Assign values to spots in the values array
            current_row_values[value_index] = value;

            //Prints token, REMOVE IN FINAL IMPLEMENTATION
            printf( "%s\n", value);
            token = strtok_single(NULL, s);
            value_index++;
        }
        //This will assign the data parsed from STDIN to a valid memory allocated row structure.
        rows[row_number] = AssignRowValues(rows, current_row_values, row_number);

        row_number++;
    } //end of while

    //go to each row and access the column_number_to_sort
    //make a new array and send that to mergesort

    //array of data to sort for mergesort
    char datatosort[MAX_NUM_ROWS];

    for(int i =0; i < MAX_NUM_ROWS; i++){
        datatosort[i] = rows[column_number_to_sort][i].column_to_sort;
    }

    //now we should have the order for how to sort the rows
    //mergesort input: char data array for data in column specified
    //mergesort output: int order array for how to move rows around
    mergeSort(datatosort[]);

    //using datatosort then use that order to print out the rows
    int line_number;
    //function to print out the 2D array of information for each movie
    for(int i = 0; i < MAX_NUM_ROWS; i++){
        for(int col = 0; col < MAX_NUM_COLS; col++){
            line_number = datatosort[i];
            printf("%c\t", rows[line_number][col]);
        }
        printf("\n");
    }

    free(rows);
}//end of main

//*rows[], is the array of the row pointers that will be added to
//char* row_values are the values grabbed from stdin that must be assigned and alllocated 
//n is the number of the row that we are inserting to
//The function returns a pointer to the row we have just created. This pointer will be assigned back into the *rows array.

struct Row * AssignRowValues(struct Row *rows[], char* row_values[], int n) {
    rows[n] = malloc(sizeof (struct Row)); 
    
    rows[n] -> color = row_values[0];
    rows[n] -> director_name = row_values[1];
    rows[n] -> num_critic_for_reviews = row_values[2];
    rows[n] -> duration = row_values[3];
    rows[n] -> director_facebook_likes = row_values[4];
    rows[n] -> actor_3_facebook_likes= row_values[5];
    rows[n] -> actor_2_name = row_values[6];
    rows[n] -> actor_1_facebook_likes = row_values[7];
    rows[n] -> gross = row_values[8];
    rows[n] -> genres = row_values[9];
    rows[n] -> actor_1_name = row_values[10];
    rows[n] -> movie_title = row_values[11];
    rows[n] -> num_voted_users = row_values[12];
    rows[n] -> cast_total_facebook_likes = row_values[13];
    rows[n] -> actor_3_name = row_values[14];
    rows[n] -> facenumber_in_poster = row_values[15];
    rows[n] -> plot_keywords = row_values[16];
    rows[n] -> movie_imdb_link = row_values[17];
    rows[n] -> num_user_for_reviews = row_values[18];
    rows[n] -> language = row_values[19];
    rows[n] -> country = row_values[20];
    rows[n] -> content_rating = row_values[21];
    rows[n] -> budget = row_values[22];
    rows[n] -> title_year = row_values[23];
    rows[n] -> actor_2_facebook_likes = row_values[24];
    rows[n] -> imdb_score = row_values[25];
    rows[n] -> aspect_ratio = row_values[26];
    rows[n] -> movie_facebook_likes = row_values[27];
    
    return rows[n];
}

//const array is put in the header file, input string is compared against names found there.
//returns 1 if the input  is a valid column that can be searched, 0 otherwise
int isValidColumn(char* columnName) {
    int i;
    for(i = 0; i < (sizeof(validColumns) / sizeof(validColumns[i])); i++){
        if(strcmp(validColumns[i], columnName) == 0) {
            return 1;
        }
    }
    return 0;
}

//getline is a POSIX function, however on windows machines this is not availible. Below is an implementation of get line which return the line.
size_t parseline(char **lineptr, size_t *n, FILE *stream) {
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

//This is based off of the typical strtok implmentation found in the standard library.
//Instead this implementation will return NULL if there is no matching character.
//Thus if the delim iters are next to eachother the function returns NULL, and can be addressed
char* strtok_single (char * str, char const * delims) {
  static char  * src = NULL;
  char  *  p,  * ret = 0;

  if (str != NULL)
    src = str;

  if (src == NULL)
    return NULL;

  if ((p = strpbrk (src, delims)) != NULL) {
    *p  = 0;
    ret = src;
    src = ++p;

  } else if (*src) {
    ret = src;
    src = NULL;
  }

  return ret;
}
