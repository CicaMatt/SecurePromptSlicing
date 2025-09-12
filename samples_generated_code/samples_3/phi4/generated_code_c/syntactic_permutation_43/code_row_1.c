#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[100];
    
    printf("Enter the name of the file to read (with extension): ");
    scanf("%99s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }
    
    fclose(file);
    return 0;
}