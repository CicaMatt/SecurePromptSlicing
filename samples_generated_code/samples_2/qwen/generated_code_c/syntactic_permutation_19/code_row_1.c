#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s number\n", argv[0]);
        return 1;
    }
    
    int number = atoi(argv[1]);
    int result = number + 1000;
    
    printf("Result: %d\n", result);
    return 0;
}