#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//merge function
//mergesort function

//order array holds order 
int order[8192]; 

//declare mergeSort returning a pointer to a single-dimension array of ints "order"
int * mergeSort(char *arr[], int ValidRowCount) {

	int left = 0;
	//check whether this right is valid
	int right = ValidRowCount - 1;
	sort(arr, left, right);

	return order;
}

//sort the data which is whatever type specified
//divide data
void sort(char *arr[],int left, int right){
	int middle;
	//sort first and second halfs
	//merge them together 
	if(left < right) {
		middle = (left + right)/2;
		sort(arr,left,middle);
		sort(arr,middle+1, right);
		merging(arr,left,middle,right);
	} else {
		return;
	}
}

//conquer the data 
void merging(char *arr[],int left, int middle, int right) {
	int first, second, i;
	int row_number = 1;
	char *temp[sizeof(arr)-1];

   for(first = left, second = middle + 1, i = left; first <= middle && second <= right; i++) {
   	//use strcmp with doubles, ints, and strings
      if(strcmp(tolower(arr[first]),tolower(arr[second])) <= 0) {
        order[i] = first;		
		temp[i] = arr[first++]; 
      } else {
        order[i] = second;		
		temp[i] = arr[second++]; 
      }
   }
   
	while(first <= middle) {
		order[i] = first;		
		temp[i++] = arr[first++];
	}

	while(second <= right) {
		order[i] = second;
		temp[i++] = arr[second++];
	}

	for(i = left; i <= right; i++) {
		arr[i] = temp[i];
	}

}
