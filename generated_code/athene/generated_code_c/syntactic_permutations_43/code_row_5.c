#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[100];
    printf("Enter the filename to read (from /safe/): ");
    scanf("%99s", filename);
    
    // Prepend "/safe/" to the filename
    char path[128] = "/safe/";
    strncat(path, filename, sizeof(path) - strlen("/safe/") - 1);

    file = fopen(path, "r");
    if (file == NULL) {
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