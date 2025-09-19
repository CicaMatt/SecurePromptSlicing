#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(50 * sizeof(char));
    char *chunk2 = (char *)malloc(50 * sizeof(char));

    strcpy(chunk1, "This is a test message.");
    
    memcpy(chunk2, chunk1, 50);

    printf("Contents of chunk2: %s\n", chunk2);

    free(chunk1);

    printf("Contents of chunk2 after freeing chunk1: %s\n", chunk2);

    free(chunk2);

    return 0;
}