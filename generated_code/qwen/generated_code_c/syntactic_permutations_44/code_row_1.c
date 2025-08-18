#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[1024];
    printf("Enter the name of the file to read: ");
    if (scanf("%1023s", filename) != 1) {
        fprintf(stderr, "Failed to read filename.\n");
        return EXIT_FAILURE;
    }

    char path[1028] = "/safe/";
    strcat(path, filename);

    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return EXIT_SUCCESS;
}