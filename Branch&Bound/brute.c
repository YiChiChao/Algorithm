#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) (a>b)?a:b



int knapsack_bruteForce(int capacity, int* profit, int* weight, int item_count){
    int a,b, c;
    if(item_count == 0 || capacity == 0)return 0;
    if(weight[item_count-1] > capacity){
        c = knapsack_bruteForce(capacity, profit, weight, item_count-1);
        return c;
    }
    else{
        a = profit[item_count-1]+knapsack_bruteForce(capacity-weight[item_count-1], profit, weight, item_count-1);
        b = knapsack_bruteForce(capacity, profit, weight, item_count-1);
        return MAX(a, b);
    }
    

}


int main(){
    int* Profit = NULL;
    int* Weight = NULL;
    int itemCount = 0;
    int Capacity = 0;
    scanf("%d %d", &itemCount, &Capacity);
    Weight = malloc(itemCount * sizeof(int));
    Profit = malloc(itemCount * sizeof(int));
    for(int i = 0; i < itemCount; ++i){
        scanf("%d %d", &(Profit[i]), &Weight[i]);
    }
    //printf("scan\n");
    printf("%d\n", knapsack_bruteForce(Capacity, Profit, Weight, itemCount));
    free(Profit);
    free(Weight);
    Profit = NULL;
    Weight = NULL;
    return 0;
}
