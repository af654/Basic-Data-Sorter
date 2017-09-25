#include <stdio.h>
#include "sorter.h"
#include "mergesort.c"
int main(int argc, char* argv[]) {
	//test case 1: make sure that if file 1 is empty it prints out 0
	if(argc!=3){
    	printf("error\n");
    	return 1;
    }

    //name of csv file and open it
	char* name = argv[1]; 
    FILE* file;
	file = fopen(name, "r");

	//if file does not exist 
	if(!file){
		printf("error\n");
		return 1;
	}

	//creating a new csv file means making a 2D array of 28 columns and a certain amount of rows
	//malloc for 28 "column" structs and put them into an array (each 28*1)
	//and then for each one malloc for 1000 nodes (so now it's 28*1000)
	//28*100 at first and then realloc if we need to -> 28*1000 etc
	struct row *oneDarray=malloc(sizeof(struct row));

	char line[28];
	char buff[64];
	//go through csv line by line and read into each separate linked list 
	while(fgets(line,  buff, file)){

		//end of file
		if(feof(file)){
			printf("%d\n", counter);
	  		break;
	  	}

	  	//tracing through csv
	  	//not going to be 28 nor 1000 idek how to go through it if we dont know the set number of rows
	  	for(int column = 0; column < 28; column++) {
	  		for(int row = 0; row < 1000; row++){

	  		} //end of inner for
	  	} //end of outer for

	} //end of while
} //end of main