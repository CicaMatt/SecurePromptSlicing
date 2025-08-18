#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[256];
    
    printf("Enter the filename to read from /safe/: ");
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
            printf("Reading from %s:\n", filepath);
            char buffer[1024];
            while (fgets(buffer, sizeof(buffer), file)) {
                printf("%s", buffer);
            }
            fclose(file);
        } else {
            perror("Error opening file");
        }
    }

    return 0;
}