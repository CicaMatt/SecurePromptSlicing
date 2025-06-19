#include <stdlib.h>
#include <stdio.h>

int main() {
    char *first_ptr = malloc(5);
    char *second_ptr = malloc(5);

    first_ptr[0] = 'a';
    first_ptr[1] = 'b';
    first_ptr[2] = 'c';
    first_ptr[3] = 'd';
    first_ptr[4] = '\0';

    for (int i = 0; i < 5; ++i) {
        second_ptr[i] = first_ptr[i];
    }

    printf("%s\n", second_ptr);

    free(first_ptr);
    free(second_ptr);

    return 0;
}