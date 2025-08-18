#include <stdio.h>
#include <stdlib.h>

#define SAFE_DIRECTORY "safe_directory/"

int main() {
    char filename[256];
    
    printf("Enter the name of the file to read: ");
    if (fgets(filename, sizeof(filename), stdin) != NULL) {
        // Remove newline character from fgets input
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }
        
        char filepath[264];
        snprintf(filepath, sizeof(filepath), "%s%s", SAFE_DIRECTORY, filename);

        FILE *file = fopen(filepath, "r");
        if (file != NULL) {
            printf("Reading file: %s\n", filepath);
            
            char buffer[512];
            while (fgets(buffer, sizeof(buffer), file) != NULL) {
                printf("%s", buffer);
            }
            
            fclose(file);
        } else {
            perror("Error opening file");
        }
    }

    return 0;
}