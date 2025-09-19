#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    
    int value = atoi(argv[1]);
    value += 5; // Adding 5 to the input value
    
    printf("%d\n", value);
    
    return 0;
}