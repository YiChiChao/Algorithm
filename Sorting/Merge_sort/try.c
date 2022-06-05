#include <stdio.h>
int main(){
    int MemArray[5] = {1,2,3,4,5};
    int* x10 = MemArray;
    int i = 5;
    int result;
    do{
        result += x10[0];
        x10++;
        i -= 1;
    }while(i > 0);
    printf("%d\n", result);
    return 0;
}
