#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[] = "/safe/file.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    return EXIT_SUCCESS;
}