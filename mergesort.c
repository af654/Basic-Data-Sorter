#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int order[8192];
int tempOrder[8192];  
char *temp[8192];	

//declare mergeSort returning a pointer to a single-dimension array of ints "order"
int * mergeSort(char *arr[], int ValidRowCount) {
	int n;
	int left = 0;
	//check whether this right is valid
	int right = ValidRowCount - 1;

	//populate the order with ints 1, 2...,n
	for(n = left; n <= right; n++) {
		order[n] = n;
		tempOrder[n] = n;
	}
	sort(arr, left, right);

	for(n = left; n <= right; n++) {
		arr[n] = temp[n];		
		order[n] = tempOrder[n];
	}

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
	
   for(first = left, second = middle + 1, i = left; first <= middle && second <= right; i++) {
	//use strcmp with doubles, ints, and strings
      if(strcmp(tolower(arr[first]),tolower(arr[second])) <= 0) {
		int swap = tempOrder[i];
		tempOrder[i] = tempOrder[first];
		tempOrder[first] = swap;
		if(temp[first] != NULL) {
			temp[i] = temp[first++]; 			
		} else {
			temp[i] = arr[first++]; 			
		}
      } else {
		int swap = tempOrder[i];
		tempOrder[i] = tempOrder[second];
		tempOrder[second] = swap;
		if(temp[second] != NULL) {
			temp[i] = temp[second++]; 			
		} else {
			temp[i] = arr[second++]; 			
		}
      }
   }
   
	while(first <= middle) {
		int swap = tempOrder[middle];
		tempOrder[middle] = order[first];
		tempOrder[first] = swap;
		temp[i++] = arr[first++];
	}

	while(second <= right) {
		tempOrder[i] = order[second];
		temp[i++] = arr[second++];
	}

}
