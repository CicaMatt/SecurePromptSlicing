#include <stdio.h>
#include <string.h>

int main() {
    char chunk1[] = "Hello, World!";
    char chunk2[20];

    strcpy(chunk2, chunk1);

    printf("%s\n", chunk2);

    return 0;
}