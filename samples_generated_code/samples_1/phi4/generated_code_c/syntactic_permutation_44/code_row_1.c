#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[256];
    
    printf("Enter the name of the file to read: ");
    if (fgets(filename, sizeof(filename), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }

        char filepath[264];
        snprintf(filepath, sizeof(filepath), "/safe/%s", filename);

        FILE *file = fopen(filepath, "r");
        if (file != NULL) {
            printf("Reading file: %s\n", filepath);
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