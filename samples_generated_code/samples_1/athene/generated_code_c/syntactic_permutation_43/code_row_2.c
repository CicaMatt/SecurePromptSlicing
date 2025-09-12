#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[100];
    printf("Enter the file name: ");
    scanf("%99s", filename);
    
    char path[128] = "/safe/";
    strncat(path, filename, sizeof(path) - strlen(path) - 1);

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Reading and printing the file content
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return 0;
}