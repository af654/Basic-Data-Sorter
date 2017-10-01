#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NUM_ROWS 8192
#define MAX_NUM_COLS 64

//merge function
//mergesort function
//sortedarr holds data
char* sortedarr;
//temp array for mergesort
char* temp;
//order array holds order 
int order[MAX_NUM_ROWS]; 

//declare mergeSort returning a pointer to a single-dimension array of ints "order"
int * mergeSort(char** arr) {
	//malloc for space for sortedarr
	sortedarr = malloc (MAX_NUM_ROWS * sizeof(char));
	//transfer contents from array to sorted array
	int i;
	for(i = 0; i < sizeof(arr); i++) {
		sortedarr[i] = (char*) malloc(sizeof(strlen(arr[i])+1));
		strcpy(sortedarr,arr[i]);
	}

	int left = 0;
	int right = (sizeof(sortedarr)/sizeof(sortedarr[0]));
	sort(left, right);

	free(sortedarr);
	free(temp);

	return order;
}

//sort the data which is whatever type specified
//divide data
void sort(int left, int right){
	int middle;
	//sort first and second halfs
	//merge them together 
	if(left < right) {
		middle = (left + right)/2;
		sort(left,middle);
		sort(middle+1, right);
		merging(left,middle,right);
	} else {
		return;
	}
}

//conquer the data 
//STILL NEED TO POPULATE THE ORDER ARRAY
void merging(int left, int middle, int right) {
	int first, second, i;
	int row_number = 1;

   for(first = left, second = middle + 1, i = left; first <= middle && second <= right; i++) {
   	//use strcmp with doubles, ints, and strings
      if(strcmp(tolower(sortedarr[first]),tolower(sortedarr[second])) <= 0) {
         temp[i] = sortedarr[first++];
      } else {
         temp[i] = sortedarr[second++];
      }
   }
   
   while(first <= middle)
      temp[i++] = sortedarr[first++];

   while(second <= right)   
      temp[i++] = sortedarr[second++];

   for(i = left; i <= right; i++)
      sortedarr[i] = temp[i];
}
