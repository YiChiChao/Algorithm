#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int compare(void* a, void* b){
    int A = *(int*)a;
    int B = *(int*)b;

    return A-B;
}

int main(){
    int ArraySize = 0;
    int targetIndex = 0;
    char filename[20];
    int* array;
    FILE* inputfile;
    FILE* outputfile = fopen("time_result.txt", "w");
    for(int j = 10000000; j <= 30000000; j += 1000000){
        for(int k = 1; k <= 3; ++k){
            memset(filename, '\0', 20);
            //sprintf(filename, "open_2.txt");
            sprintf(filename, "open_%d_%d", j, k);
            inputfile = fopen(filename, "r");

            fscanf(inputfile, "%d %d", &ArraySize, &targetIndex);
            array = malloc(ArraySize * sizeof(int));
            for(int i = 0; i < ArraySize; ++i){
                fscanf(inputfile,"%d", &(array[i]));
            }

            double start_time = omp_get_wtime();
            qsort(array, ArraySize, sizeof(int), compare);
            printf("%d_%d :%d\n", j, k, array[targetIndex-1]);
            double end_time = omp_get_wtime();
            //printf("%g\n\n", end_time - start_time);
            //fprintf(outputfile, "%g\n",end_time - start_time);
            fprintf(outputfile, "%d_%d :%d\n", j, k, array[targetIndex-1]);
            free(array);
            array = NULL;
        }
    }
    
    return 0; 

}