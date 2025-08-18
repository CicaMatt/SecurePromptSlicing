#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[100];
    printf("Enter the filename: ");
    scanf("%99s", filename);
    
    char fullpath[128];
    snprintf(fullpath, sizeof(fullpath), "/safe/%s", filename);

    FILE *file = fopen(fullpath, "r");
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