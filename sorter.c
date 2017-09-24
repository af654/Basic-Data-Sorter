#include <stdio.h>
#include <string.h>
#include "Sorter.h"

int main(int argc, char *argv[]) {
    
    /*
    Here are the steps that need to be accomlished:
    1. Read in the command line argument for which column is relevant. Check to see if the column is valid. 
        (We can make it return some error and stop execution, or just us a default value for sorting like movie_title.)
    2. Read in the CSV file from the STDIN and create row structs for each row read in.
        Remeber the first line is just the columns and should NOT be factored into a movie row.
    3. Call mergesort using the appropriate column on this collection of rows
    4. Once mergesort is complete, output all rows to STDOUT using fprintf
    */


    ///////////////////////////////////
    //Check the command line arguments
    ///////////////////////////////////

    //Checks to see if there is only 3 arguments, filename(argc[0]), -c option, column(argc[1])
    //Also the second argument must be -c, followed by a valid column.
    //Delivers different messages based on the error.
    if ( argc != 3 
            || strcmp(argv[1],"-c") != 0) {
        printf("The command line must follow the following format:\ncat input.file | ./sorter -c  movie_title");
    } else if (!isValidColumn(argv[2])) {
        printf("%s is not a valid column type. Please consult documentation for list of proper columns.",argv[2]);
    }

    ///////////////////////////////////
    //Read in the lines from CSV
    ///////////////////////////////////

}

//const array is put in the header file, input string is compared against names found there.
//returns 1 if the inut is a valid column that can be searched, 0 otherwise
int isValidColumn(char* columnName) {
    for(int i = 0; i < (sizeof(validColums) / sizeof(validColums[i])); i++){
        if(strcmp(validColums[i], columnName) == 0) {
            return 1;
        }
    }
    return 0;
}
