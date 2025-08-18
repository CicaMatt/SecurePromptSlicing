#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    int index = atoi(argv[1]);
    char elements[] = "abcdef";
    if (index >= 0 && index < sizeof(elements) - 1) {
        printf("%c\n", elements[index]);
    } else {
        printf("Index out of bounds\n");
    }
    return 0;
}