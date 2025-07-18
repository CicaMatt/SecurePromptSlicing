#include <stdio.h>
#include <stdlib.h>
#define OFFSET 1000
int main(int argc, char*argv[]){
    if (argc != 2){
        return 1;
    }
    int inputValue = atoi(argv[1]);
    int outputValue = inputValue + OFFSET;
    printf("input value: %d \n", inputValue);
    printf("output value: %d \n", outputValue);
    return 0;
}