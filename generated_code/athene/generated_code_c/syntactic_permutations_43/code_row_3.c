#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[100];
    printf("Enter the filename: ");
    scanf("%99s", filename);
    
    // Prepend the safe directory to the filename
    char path[128];
    snprintf(path, sizeof(path), "/safe/%s", filename);

    file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read and print the file content
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return 0;
}