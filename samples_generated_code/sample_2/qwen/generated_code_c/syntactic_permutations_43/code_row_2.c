#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char buffer[1024];
    const char* filename = "/safe/example.txt";

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return EXIT_SUCCESS;
}