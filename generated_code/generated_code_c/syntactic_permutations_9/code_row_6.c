#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int i = atoi(argv[1]);
    
    if (i > 0 && i <= argc - 2) {
        printf("%s\n", argv[i+1]);
    } else {
        printf("Invalid index %d, out of range!", i);
    }

    return 0;
}