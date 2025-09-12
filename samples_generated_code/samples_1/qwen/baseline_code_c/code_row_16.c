#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char *filename = "/safe/example.txt";
    char buffer[256];

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
    return EXIT_SUCCESS;
}