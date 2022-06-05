#include<stdio.h>
#include<stdlib.h>
void swap(int* arr, int i, int j);
int partition(int* arr, int i, int j);

void swap(int* arr, int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
int partition(int* arr, int i, int j){
    /*set the first index of the arr as the pivot*/
    int pivot_index = i;
    int pivot = arr[i];
    
    while(i <= j){
        while(arr[i] <= pivot && i <= j) ++i;
        while(arr[j] >= pivot && i <= j) --j;
        if(i < j) swap(arr, i, j);
    }
    swap(arr, pivot_index, j);
    return j;
}

void quicksort(int* arr, int i, int j){
    int pi;
    if(i >= j) return;
    if(i < j){
        pi = partition(arr, i, j);
    }
    quicksort(arr, i, pi-1);
    quicksort(arr, pi+1, j);
}

int main(){
    int arr[] = {16, 20, 1, 26, 14, 7, 9, 4, 8, 18, 11, 17};
    quicksort(arr, 0, 11);
    printf("arr ={");
    for(int i = 0; i < 12; ++i){
        printf(" %d%c", arr[i], ','*(i != 11)+'}'*(i == 11));
    }
    printf("\n");
}