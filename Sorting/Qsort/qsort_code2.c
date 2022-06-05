#include<stdio.h>
#include<stdlib.h>
void swap(int* arr, int i, int j);
int partition(int* arr, int i, int j);

void swap(int* arr, int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int partition(int* arr, int low, int high){
    int pivot_index = low;
    int pivot = arr[low];
    int i = low;
    int j = low+1;
    while( j <= high){
        if(arr[j] >= pivot){
            ++j;
            continue;
        }
        if(arr[j] < pivot){
            ++i;//record the last index of the small number array for the last swap with the pivot
            swap(arr, i, j);
            ++j;
        }
    }
    swap(arr, pivot_index, i);
    return i;

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