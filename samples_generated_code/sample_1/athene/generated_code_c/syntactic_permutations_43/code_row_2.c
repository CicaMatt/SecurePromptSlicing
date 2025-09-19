#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[100];
    printf("Enter the filename: ");
    scanf("%s", filename);
    
    char path[120] = "/safe/";
    strncat(path, filename, 99 - strlen(path));

    FILE *file = fopen(path, "r");
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