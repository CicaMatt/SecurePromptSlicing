#include <stdio.h>
#include <stdlib.h>

int main() {
    char *elements[] = {"apple", "banana", "cherry", "date", "elderberry"};
    int index = atoi("2");
    printf("%s\n", elements[index]);
    return 0;
}