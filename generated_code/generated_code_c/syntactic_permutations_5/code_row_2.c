#include <stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    if (argc == 2){
        int index = atoi(argv[1]);
        printf("element at %d is: %d\n",index, arr[index]);
    }
    return 0;
}