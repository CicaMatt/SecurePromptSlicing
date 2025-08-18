#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[256];
    char buffer[1024];

    printf("Enter the filename to read from /safe/: ");
    if (scanf("%255s", filename) != 1) {
        fprintf(stderr, "Failed to read filename.\n");
        return EXIT_FAILURE;
    }

    char path[261] = "/safe/";
    strcat(path, filename);

    file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
    return EXIT_SUCCESS;
}