#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[1024];
    printf("Enter the name of the file to read: ");
    if (fgets(filename, sizeof(filename), stdin) != NULL) {
        // Remove newline character from the end of the string if present
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }
    }

    char path[1034] = "/safe/";
    strncat(path, filename, sizeof(path) - strlen(path) - 1);

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return EXIT_SUCCESS;
}