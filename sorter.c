#include <stdio.h>
#include <string.h>
#include "Sorter.h"
#include "mergesort.c"

#define MAX_NUM_ROWS 5044
#define MAX_NUM_COLS 64

int ValidRowCount = 0;
int ValidColumnCount = 0;

int main(int argc, char* argv[]) {
    int i,j,n;
    int column_number_to_sort; 
    int *properOrder;
    Row *rows[MAX_NUM_ROWS];
    char* column_to_sort; 
    char *datatosort[MAX_NUM_ROWS];

    if ( argc != 3 || strcmp(argv[1],"-c") != 0) {
        printf("The command line must follow the following format:\ncat input.file | ./sorter -c  movie_title");
        return 0;
    } else if (!isValidColumn(argv[2])) {
        printf("%s is not a valid column type. Please consult documentation for list of proper columns.",argv[2]);
        return 0;
    }

    column_to_sort = argv[2];
    //search function on validcolumns
    for(n = 0; n < (sizeof(validColumns) / sizeof(validColumns[n])); n++){
        if(strcmp(validColumns[n], column_to_sort) == 0) {
            column_number_to_sort = n;
            break;
        }
    }

    //Loop through STDIN and use the implemented parseline() to get the whole line to put into an allocated row struct.
    while(!feof(stdin)) {
        char* line = NULL;
        char* value;  
        char* token;
        char* current_row_values[MAX_NUM_COLS];
        int value_index = 0;        
        size_t size;

        if(ValidColumnCount > 0 && rows[ValidColumnCount - 1] == 0x0) {
            break;
        }
        
        parseline(&line, &size, stdin);
        //Skip the first row
        if(ValidRowCount == 0) {
            line = NULL;
            parseline(&line, &size, stdin);
        }
        ValidRowCount++;        
        token = strtok_single(line, ",");

        //Walk through other tokens on the line
        while(token) {
            
            //If the value we are reading in is Null, we want to replace it with the string "<EMPTY>"
            value = *token ? token : "<EMPTY>";
            
            //Assign values to spots in the values array
            current_row_values[value_index] = value;

            //Tokenizes the string based on ','
            token = strtok_single(NULL, ",\n");
            value_index++;
        }
        //This will assign the data parsed from STDIN to a valid memory allocated row structure.
        rows[ValidColumnCount] = assignRowValues(rows, current_row_values, ValidColumnCount);
        
        ValidColumnCount++;
        
    } //end of while

    //go to each row and access the column_number_to_sort
    //make a new array and send that to mergesort
    //array of data to sort for mergesort
    for(j = 0; j < ValidRowCount - 1; j++){
        datatosort[j] = getRowColumnValue(rows,j,column_number_to_sort);
    }

    //now we should have the order for how to sort the rows
    //mergesort input: char data array for data in column specified
    //mergesort output: int order array for how to move rows around
    //int * mergeSort(char *arr[], int ValidRowCount, char* sortColType, int colIndex)
    //char* sortColType = getSortColType(int column_number_to_sort);
    properOrder = mergeSort(datatosort, ValidRowCount - 1);
    
    //print top bar to CSV
    printf("color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes\n");

    for(i = 0; i < ValidRowCount - 1; i++){
        struct Row *correctRow = rows[properOrder[i]];
        printRowToCSV(correctRow, i);
    }

    for(i = 0; i < ValidRowCount; i++) {
        free(rows[i]);
    }

}//end of main

void printRowToCSV(struct Row *correctRow, int rowIndex) {
    int c = 0;
    for (c = 0; c < 27; c++) {
        printf("%s", getSingleRowValues(correctRow, c));
        printf(",");
    } 
    printf("%s", getSingleRowValues(correctRow, c));    
}

//This first overload will work on a single row, and return the assignments for that row
char* getSingleRowValues(struct Row *row, int columnIndex) {
    switch (columnIndex) {
        case 0:
            return row -> color;
        case 1:
            return row -> director_name;
        case 2:
            return row -> num_critic_for_reviews;
        case 3:
            return row -> duration;
        case 4:
            return row -> director_facebook_likes;
        case 5:
            return row -> actor_3_facebook_likes;
        case 6:
            return row -> actor_2_name;
        case 7:
            return row -> actor_1_facebook_likes;
        case 8:
            return row -> gross;
        case 9:
            return row -> genres;
        case 10:
            return row -> actor_1_name;
        case 11:
            return row -> movie_title;
        case 12:
            return row -> num_voted_users;
        case 13:
            return row -> cast_total_facebook_likes;
        case 14:
            return row -> actor_3_name;    
        case 15:
            return row -> facenumber_in_poster;    
        case 16:
            return row -> plot_keywords;    
        case 17:
            return row -> movie_imdb_link;    
        case 18:
            return row -> num_user_for_reviews;    
        case 19:
            return row -> language;    
        case 20:
            return row -> country;    
        case 21:
            return row -> content_rating;    
        case 22:
            return row -> budget;    
        case 23:
            return row -> title_year;    
        case 24:
            return row -> actor_2_facebook_likes;    
        case 25:
            return row -> imdb_score;    
        case 26:
            return row -> aspect_ratio;    
        case 27:
            return row -> movie_facebook_likes;    
        default:
            return row -> movie_title;
    }
}

//*rows[], is the array of the row pointers that will be added to
//char* row_values are the values grabbed from stdin that must be assigned and alllocated 
//n is the number of the row that we are inserting to
//The function returns a pointer to the row we have just created. This pointer will be assigned back into the *rows array.
char* getRowColumnValue(struct Row *rows[], int i, int j) {
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

struct Row * assignRowValues(struct Row *rows[], char* row_values[], int n) {
    //We want to throw out duplications of movies based on title
    if(n != 0 && strcmp(row_values[11], rows[n-1] -> movie_title) == 0) {
        return 0x0;
    }
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
        bufptr = malloc(4096);
        if (bufptr == NULL) {
            return -1;
        }
        size = 4096;
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
//Thus if the delimiters are next to eachother the function returns NULL, and can be addressed
char* strtok_single (char * string, char const * delimiter) {
    static char *source = NULL;
    char *p, *result = 0;
    if(string != NULL)         source = string;
    if(source == NULL)         return NULL;
 
    if((p = strpbrk (source, delimiter)) != NULL) {
       *p  = 0;
       result = source;
       source = ++p;
    }
 return result;
}

int findType(char* token) {
    int length,i; 

    length = strlen (token);
    for (i = 0; i < length; i++) {
        //If a character is not a digit but it is also not a period it must be a string
        if (!isdigit(token[i]) && token[i] != '.') {
            return 1;
        } else { //otherwise it is a double
            return 2;
        } 
    } //If we never encounter a non-numerical it must be an integer
    return 0;
}
