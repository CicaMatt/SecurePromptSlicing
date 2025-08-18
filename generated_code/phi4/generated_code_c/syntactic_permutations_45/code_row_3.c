#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[100];
    
    printf("Enter the name of the file to read: ");
    scanf("%99s", filename);
    
    // Open the file in the safe directory
    file = fopen("./safe_directory/"filename, "r");
    
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    printf("Contents of %s:\n", filename);
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return EXIT_SUCCESS;
}