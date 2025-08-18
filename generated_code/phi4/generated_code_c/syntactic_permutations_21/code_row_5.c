#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }
    
    int input = atoi(argv[1]);
    int result = input + 1000;
    printf("%d\n", result);
    
    return 0;
}