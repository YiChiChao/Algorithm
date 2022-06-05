#include<stdio.h>
#include<stdlib.h>

void bubble_sort(int* array, int n){
    int t = 0;//to avoid the init variable cannot go into the loop
    int swap = 0;
    while(!(swap == 0 && t != 0)){
        swap = 0;
        for(int i = 0; i < n-t-1; ++i){
            //swap
            if(array[i] > array[i+1]){
                int tmp = array[i];
                array[i] = array[i+1];
                array[i+1] = tmp;
                swap += 1;
            }
        }
        t += 1;
    }
}
int main(){
    int array[6] = {5, 1, 4, 2, 8};
    bubble_sort(array, 5);
    for(int i = 0; i < 5; ++i){
        printf("%d%c", array[i], ','*(i != 4) + '\n'*(i == 4));
    }
    return 0;
}