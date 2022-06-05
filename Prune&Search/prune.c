#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
int prune_search(int* array, int target, int start, int end);
void swap(int* a, int* b);
void insertion_sort(int* array, int start, int end){
    int current = 0;
    for(int i = 1; start+i <= end; ++i){
        current = array[start+i];
        int j;
        for(j = start+i-1; j >= start ; --j){
            if(array[j] > current)array[j+1] = array[j];
            else break;
        }
        array[j+1] = current;
    }

    //test

    /*printf("-------AFTER ORDERED -------\n");
    for(int i = 0; start+i <= end; ++i){
        printf("%d ", array[start+i]);
    }printf("\n");*/
}



int median(int* array, int start, int end, int arraySize){
    int numofMedian = (end-start+5)/5;
    int substart, subend; //record the subarray start and end
    int MedianIdx;
    for(int i = 0; i < numofMedian; ++i){
        substart = start + i*5;
        subend = substart + 4;
        if(subend > end) subend = end;
        //recursively find the meduan of the subarray
        MedianIdx = prune_search(array, (subend-substart)/2 , substart, subend);
        //printf("median = %d index = %d\n", array[MedianIdx], MedianIdx);
        //set the first five number as those medians
        swap(&(array[start+i]), &(array[MedianIdx]));
    }
    /*printf("--------Medians--------------\n");
    for(int i = start; i < start + numofMedian; ++i){
        printf("%d ", array[i]);
    }printf("\n");*/
    return prune_search(array, ((numofMedian)/2)-1 , start, start+numofMedian-1);
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* array, int start, int end, int median){
    int target = array[median];
    swap(&(array[start]), &(array[median]));
    // i is the pointer pointing at the ordered array, j pointing to the target
    int i, j; 
    for(i = start, j = start+1; j <= end; ++j){
        if(array[j] <= target) swap(&(array[j]), &(array[++i]));
    }
    swap(&(array[i]), &(array[start]));
    return i;
    //              result:
    // nums < target |target| nums > target
}

int prune_search(int* array, int target, int start, int end){
    int arraySize = end-start+1;
    //when the array size is less or equal to 5
    if(arraySize <= 5){
        //printf("start: %d end: %d\n", start, end);
        insertion_sort(array, start, end);
        return start+target;
    }

    int pivot = median(array, start, end, arraySize);
    
    pivot = partition(array, start, end, pivot);
    //if(target == 36114 || target == 541159) printf("pivot = %d target = %d\n", pivot, target);
    
    /*for(int i = start; i <= end; ++i){
        printf("%d ", array[i]);
    }printf("\n");*/

    if(pivot < start+target){
        //printf("big\n");
        return prune_search(array, target-(pivot-start+1), pivot+1, end);
    }
    else if(pivot > start+target) {
        //printf("small\n");
        return prune_search(array, target, start, pivot-1);
    }
    else return pivot;
}

int main(){
    int ArraySize = 0;
    int targetIndex = 0;
    char filename[20];
    int* array;
    int ansIdx;
    FILE* inputfile;
    FILE* outputfile = fopen("time_result_prune.txt", "w");
    FILE* answerfile = fopen("prune_ans.txt", "w");
    for(int j = 10000000; j <= 30000000; j += 1000000){
        for(int k = 1; k <= 3; ++k){
            memset(filename, '\0', 20);
            //sprintf(filename, "open_2.txt");
            sprintf(filename, "open_%d_%d", j, k);
            inputfile = fopen(filename, "r");

            fscanf(inputfile, "%d %d", &ArraySize, &targetIndex);
            //printf("%d\n", targetIndex);
            array = malloc(ArraySize * sizeof(int));
            for(int i = 0; i < ArraySize; ++i){
                fscanf(inputfile,"%d", &(array[i]));
            }
            double start_time = omp_get_wtime();
            ansIdx = prune_search(array, targetIndex-1, 0, ArraySize-1);
            printf("%d_%d :%d\n", j, k, array[ansIdx]);
            double end_time = omp_get_wtime();
            fprintf(answerfile, "%d\n", array[ansIdx]);
            fprintf(outputfile, "%g\n",end_time - start_time);
            fclose(inputfile);
            free(array);
            array = NULL;
        }
    }
    fclose(answerfile);
    fclose(outputfile);
    return 0;
}