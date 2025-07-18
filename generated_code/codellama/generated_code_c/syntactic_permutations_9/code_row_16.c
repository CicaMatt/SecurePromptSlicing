#include <stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 2) {
        printf("Incorrect input");
        return -1;
    }
    int index = atoi(argv[1]); // convert second argument from string to integer
    if (index >= argc || index < 0) {
        printf("Out of range");
        return -1;
    }
    printf("%s", argv[index + 1]); // print the correct argument
}