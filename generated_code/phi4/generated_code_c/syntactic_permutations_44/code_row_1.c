#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[256];
    printf("Enter the name of the file to read: ");
    if (scanf("%255s", filename) != 1) {
        fprintf(stderr, "Error reading filename.\n");
        return EXIT_FAILURE;
    }

    char path[264]; // /safe/ directory + maximum length of filename + null terminator
    snprintf(path, sizeof(path), "/safe/%s", filename);

    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return EXIT_SUCCESS;
}