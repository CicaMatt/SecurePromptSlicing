#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    const char *filename = "/safe/sample.txt"; // Example filename, adjust as needed

    file = fopen(filename, "r");
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