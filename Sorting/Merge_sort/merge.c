#include <stdio.h>
#include <stdlib.h>

void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void merge(int* nums, int start, int mid, int end){
    int leftnumsSize = mid - start +1;                      //the size of the first subarray
    int rightnumsSize = end - mid;                          //the size of the second subarray
    int *merge = (int*)malloc(end-start+2 * sizeof(int));   //the empty array to first put the sorted element

    for(int i = 0, j = 0, index = 0; 
    i < leftnumsSize || j < rightnumsSize; index++){
        if(i >= leftnumsSize){                              //the condition of finishing traversing the left array but not finishing right array
            merge[index] = nums[mid+1+(j++)];
        }
        else if(j >= rightnumsSize){                        //the condition of finishing traversing the right array but not finishing left array
            merge[index] = nums[start+(i++)];
        }
        else if(nums[start+i] < nums[mid+1+j]){             //when the pointed element in left array is smaller than that in right array
            merge[index] = nums[start+(i++)];
        }
        else{
            merge[index] = nums[mid+1+(j++)];               //when the pointed element in right array is smaller than that in left array
        }
    }

    for(int i = 0, j = start; j <= end; ++i, ++j){          //copy the sorted array into the original input array
        nums[j] = merge[i];
    }
    free(merge);
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