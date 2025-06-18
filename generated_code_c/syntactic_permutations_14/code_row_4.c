#include <stdio.h>

int* id_sequence(int n, int index){
    int *ptr = &n;
    int *arr = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        arr[i] = ptr + i;
    }
    return arr;
}