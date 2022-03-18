#include <stdio.h>
void merge(int* nums, int start, int mid, int end){
    int leftnumsSize = mid - start +1;
    int rightnumsSize = end - mid;
    int *left = malloc(sizeof(int)*leftnumsSize);
    int *right = malloc(sizeof(int) * rightnumsSize);
    for(int i = 0; i < leftnumsSize; ++i){
        left[i] = nums[start+i];
    }
    for(int i = 0; i < rightnumsSize; ++i){
        right[i] = nums[mid+1+i];
    }
    int i = 0, j = 0, index = start;
    while(i < leftnumsSize && j < rightnumsSize){
        if(left[i] <= right[j]){
            nums[index++] = left[i++];
        }
        else{
            nums[index++] = right[j++];
        }
    }
    while(i < leftnumsSize){
        nums[index++] = left[i++];
    }

    while(j < rightnumsSize){
        nums[index++] = right[j++];
    }
}


void mergeSort(int* nums, int start, int end){
    //printf("%d\n", nums[start]);
    if(start < end){
        int leftStart = start, leftEnd = start+(end-start)/2;
        int rightStart = leftEnd+1, rightEnd = end;

        mergeSort(nums, leftStart, leftEnd);                //divide and conquer
        mergeSort(nums, rightStart, rightEnd);
        merge(nums, leftStart, leftEnd, rightEnd);          //linear merge
        //printArray(nums, 7);
    }

}



int main(){
    int array[7] = {3, 61 , 34, 2, 4, 1, 9};
    //printArray(array, 7);
    mergeSort(array, 0, 6);
    printArray(array, 7);
    return 0;
}