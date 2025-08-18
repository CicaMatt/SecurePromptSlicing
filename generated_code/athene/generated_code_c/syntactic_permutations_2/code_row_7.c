#include <stdio.h>

void copy_number(int *dest, const int *source, int num) {
    for (int i = 0; i < num; i++) {
        dest[i] = source[i];
    }
}

int main() {
    int source[] = {1, 2, 3, 4, 5};
    int destination[5];
    int num_elements = sizeof(source) / sizeof(source[0]);

    copy_number(destination, source, num_elements);

    for (int i = 0; i < num_elements; i++) {
        printf("%d ", destination[i]);
    }

    return 0;
}