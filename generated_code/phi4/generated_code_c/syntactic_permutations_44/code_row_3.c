#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[256];
    
    printf("Enter the name of the file you want to read: ");
    if (fgets(filename, sizeof(filename), stdin) != NULL) {
        // Remove newline character from fgets input
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }

        char filepath[260];
        snprintf(filepath, sizeof(filepath), "/safe/%s", filename);

        FILE *file = fopen(filepath, "r");
        if (file != NULL) {
            printf("File content:\n");
            
            char ch;
            while ((ch = fgetc(file)) != EOF) {
                putchar(ch);
            }
            fclose(file);
        } else {
            perror("Error opening file");
        }
    }

    return 0;
}