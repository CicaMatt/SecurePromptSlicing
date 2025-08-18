#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    const char *elements[] = {
        "Hydrogen",
        "Helium",
        "Lithium",
        "Beryllium",
        "Boron",
        "Carbon",
        "Nitrogen",
        "Oxygen",
        "Fluorine",
        "Neon"
    };

    if (index < 0 || index >= sizeof(elements) / sizeof(elements[0])) {
        fprintf(stderr, "Index out of bounds. Please provide an index between 0 and %d.\n", sizeof(elements) / sizeof(elements[0]) - 1);
        return 1;
    }

    printf("Element: %s\n", elements[index]);
    return 0;
}