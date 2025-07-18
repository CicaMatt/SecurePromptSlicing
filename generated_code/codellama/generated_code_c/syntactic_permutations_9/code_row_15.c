#include <stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]) {
    if (argc > 1) {
        int index = atoi(argv[1]);
        if (index > 0 && index <= argc) {
            printf("%s\n", argv[index]);
        } else {
            printf("Invalid argument!\n");
        }
    } else {
        printf("No arguments provided!\n");
    }
    return 0;
}