#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int order[5044];
char *temp[5044];	

//declare mergeSort returning a pointer to a single-dimension array of ints "order"
int * mergeSort(char *arr[], int ValidRowCount) {
	int i;
	char **unsorted = malloc(sizeof(char *) * ValidRowCount);
	for (i = 0; i < ValidRowCount; i++) {
		unsorted[i] = malloc(strlen(arr[i]));
		strcpy(unsorted[i],arr[i]);
	}

	int left = 0;
	int right = ValidRowCount - 1;

	sort(arr, left, right);

	//take the contents of temp (which is the sorted arr) and compare them to unsorted arr 
	int k=0;
	for(i = 0; i < ValidRowCount; i++){
		int j = 0;
		for(j = 0; j < ValidRowCount; j++){
			//if they are the same string
			if(strcmp(tolower(arr[i]),tolower(unsorted[j])) == 0) {
				//order[k] = (int *)malloc(sizeof(int));
				order[k] = j;
				k++;
				break;
			}
		}
	}
	int l;
	for (l = 0; l < ValidRowCount; l++) {
		free(unsorted[l]);
	}
	free(unsorted);

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
		temp[i] = arr[first++]; 			
	} else {
		temp[i] = arr[second++]; 						
		}
	}

	while(first <= middle) {
		temp[i++] = arr[first++];
	}

	while(second <= right) {
		temp[i++] = arr[second++];
	}

	for(i = left; i <= right; i++){
		arr[i]= temp[i];
	}

}
