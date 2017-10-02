#include <stdio.h>
#include <string.h>
#include "Sorter.h"
#include "mergesort.c"

#define MAX_NUM_ROWS 8192
#define MAX_NUM_COLS 64

int ValidRowCount = 0;
int ValidColumnCount = 0;

int main(int argc, char* argv[]) {
    //2D array of structs
    Row *rows[MAX_NUM_ROWS];
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
        ValidRowCount++;        
        token = strtok_single(line, s);

        //Walk through other tokens on the line
        while(token) {
            //If the value we are reading in is Null, we want to replace it with the string "<EMPTY>"
            value = *token ? token : "<EMPTY>";
            
            //Assign values to spots in the values array
            current_row_values[value_index] = value;

            //Prints token, REMOVE IN FINAL IMPLEMENTATION
            token = strtok_single(NULL, s);
            value_index++;
        }
        //This will assign the data parsed from STDIN to a valid memory allocated row structure.
        rows[ValidColumnCount] = AssignRowValues(rows, current_row_values, ValidColumnCount);

        ValidColumnCount++;
    } //end of while

    //go to each row and access the column_number_to_sort
    //make a new array and send that to mergesort
    //array of data to sort for mergesort
    char *datatosort[5];
    int j;
    for(j = 0; j < ValidRowCount; j++){
        datatosort[j] = GetRowColumnValue(rows,j,column_number_to_sort);
    }

    //now we should have the order for how to sort the rows
    //mergesort input: char data array for data in column specified
    //mergesort output: int order array for how to move rows around
    int *properOrder = mergeSort(datatosort, ValidRowCount);

    //using datatosort then use that order to print out the rows
    int line_number;
    //function to print out the 2D array of information for each movie
    int i;
    for(i = 0; i < ValidRowCount; i++){
        printRowToCSV(rows, i);
        printf("\n");
    }

    for(i = 0; i < ValidRowCount; i++) {
        free(rows[i]);
    }
    return 0;   
}//end of main

void printRowToCSV(Row *rows, int i) {
    int j;
    for (int j = 0; j < ; j++) {
        char *value = GetRowColumnValue(rows,i,j);  
        //printf(value+",")      
    }
    
}

//*rows[], is the array of the row pointers that will be added to
//char* row_values are the values grabbed from stdin that must be assigned and alllocated 
//n is the number of the row that we are inserting to
//The function returns a pointer to the row we have just created. This pointer will be assigned back into the *rows array.

char* GetRowColumnValue(struct Row *rows[], int i, int j) {
    switch (j) {
        case 0:
            return (*rows[i]).color;
        case 1:
            return (*rows[i]).director_name;
        case 2:
            return (*rows[i]).num_critic_for_reviews;
        case 3:
            return (*rows[i]).duration;
        case 4:
            return (*rows[i]).director_facebook_likes;
        case 5:
            return (*rows[i]).actor_3_facebook_likes;
        case 6:
            return (*rows[i]).actor_2_name;
        case 7:
            return (*rows[i]).actor_1_facebook_likes;
        case 8:
            return (*rows[i]).gross;
        case 9:
            return (*rows[i]).genres;
        case 10:
            return (*rows[i]).actor_1_name;
        case 11:
            return (*rows[i]).movie_title;
        case 12:
            return (*rows[i]).num_voted_users;
        case 13:
            return (*rows[i]).cast_total_facebook_likes;
        case 14:
            return (*rows[i]).actor_3_name;    
        case 15:
            return (*rows[i]).facenumber_in_poster;    
        case 16:
            return (*rows[i]).plot_keywords;    
        case 17:
            return (*rows[i]).movie_imdb_link;    
        case 18:
            return (*rows[i]).num_user_for_reviews;    
        case 19:
            return (*rows[i]).language;    
        case 20:
            return (*rows[i]).country;    
        case 21:
            return (*rows[i]).content_rating;    
        case 22:
            return (*rows[i]).budget;    
        case 23:
            return (*rows[i]).title_year;    
        case 24:
            return (*rows[i]).actor_2_facebook_likes;    
        case 25:
            return (*rows[i]).imdb_score;    
        case 26:
            return (*rows[i]).aspect_ratio;    
        case 27:
            return (*rows[i]).movie_facebook_likes;    
        default:
            return (*rows[i]).movie_title;
        }
}

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
