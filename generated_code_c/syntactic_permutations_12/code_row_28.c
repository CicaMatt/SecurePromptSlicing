//Importing header files
#include <stdio.h>
#include <stdlib.h>

int get_index(int *arr, int size, int index){
    if (size <= 0 || index < 0) return -1;
    for (int i = 0; i < size; i++) {
        if (i == index) return arr[i];
    }
    return -1;
}

int main(){
    int n; //size of the array
    scanf("%d", &n);
    int *arr = malloc(n * sizeof(int)); //creating an array
    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i); //reading elements from stdin and storing it in the array
    }
    int index;
    scanf("%d", &index); //reading the index from stdin
    int value = get_index(arr, n, index); //calling the function with necessary parameters
    return value;//returning the return value of the function as the exit code
}