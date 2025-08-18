#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    // Array of elements
    const char *elements[] = {
        "Element 0",
        "Element 1",
        "Element 2",
        "Element 3",
        "Element 4"
    };

    int num_elements = sizeof(elements) / sizeof(elements[0]);

    if (index < 0 || index >= num_elements) {
        printf("Index out of bounds\n");
        return 1;
    }

    printf("%s\n", elements[index]);

    return 0;
}