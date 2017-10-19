#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int order[5044];
char *temp[5044];
char* colType;
int colIdx;

//declare mergeSort returning a pointer to a single-dimension array of ints "order"
int * mergeSort(char *arr[], int ValidRowCount, char* sortColType, int colIndex) {
	colIdx = colIndex;
	colType = sortColType;
	int i,left,right,k,l;
	char **unsorted = malloc(sizeof(char *) * ValidRowCount);
	for (i = 0; i < ValidRowCount; i++) {
		unsorted[i] = malloc(strlen(arr[i]));
		strcpy(unsorted[i],arr[i]);
	}

	left = 0;
	right = ValidRowCount - 1;

	sort(arr, left, right);

	//take the contents of temp (which is the sorted arr) and compare them to unsorted arr 
	k = 0;
	for(i = 0; i < ValidRowCount; i++){
		int j = 0;
		for(j = 0; j < ValidRowCount; j++){
			//if they are the same string and this film hasnt been found yet
			if(strcmp(tolower(arr[i]),tolower(unsorted[j])) == 0) {
				//Convert the index to a string and tage it with the index.
				//A string tagged with its index has been removed. 
				char str[12];
				sprintf(str, "%d", j);
				unsorted[j] = strcat(unsorted[j], str);
				order[k] = j;
				k++;
				break;
			}
		}
	}

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
    //if(strcmp(tolower(arr[first]),tolower(arr[second])) <= 0) {
    if(compare(arr[], unsortedarr[], first, second) <= 0) {
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

long compare(char *arr[], char *unsortedarr[], first, second)
{
    const char* r1Value = arr[first];
    const char* r2Value = unsortedarr[second];
    
    if (strcmp(colType, "char") == 0) {
        // if the value starts with a quote advancee to the next character
        if (*r1Value == '"') {
            r1Value++;
        }
        if (*r2Value == '"') {
            r2Value++;
        }
        return(strcmp(r1Value, r2Value));
    }
    else if (strcmp(colType, "int") == 0){
                int i1Value = atoi(r1Value);
                int i2Value = atoi(r2Value);
                return (i1Value - i2Value);
    } else if (strcmp(colType, "long") == 0) {
                long l1Value = atol(r1Value);
                long l2Value = atol(r2Value);
                return (l1Value - l2Value);
    }
    else if (strcmp(colType, "float") == 0) {
                float f1Value = atof(r1Value);
                float f2Value = atof(r2Value);
                return (f1Value - f2Value);
    } else {
        //fprintf(stderr, "Unknown colType: %s\n", colType);
        exit(1);
    }
}
