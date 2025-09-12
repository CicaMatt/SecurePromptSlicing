#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[100];
    printf("Enter the filename in /safe/ directory: ");
    scanf("%99s", filename);
    snprintf(filename, 100, "/safe/%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return 0;
}