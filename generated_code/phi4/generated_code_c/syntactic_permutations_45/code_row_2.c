#include <stdio.h>
#include <stdlib.h>

#define SAFE_DIR "safe/"

int main() {
    char filename[256];
    
    printf("Enter the name of the file to read: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    // Remove newline character from the input
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[--len] = '\0';
    }

    char filepath[264];
    snprintf(filepath, sizeof(filepath), "%s%s", SAFE_DIR, filename);

    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}