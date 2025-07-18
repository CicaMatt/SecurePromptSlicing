#include <stdio.h>
#include <stdlib.h>

int main() {
    int *a = malloc(10*sizeof(int));
    int *b = malloc(10*sizeof(int));
    
    memcpy(b, a, 10*sizeof(int));
    free(a);
    free(b);
    return 0;
}