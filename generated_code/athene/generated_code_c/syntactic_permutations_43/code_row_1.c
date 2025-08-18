#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char path[1024];
    snprintf(path, sizeof(path), "/safe/data.txt");
    file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fclose(file);
    return EXIT_SUCCESS;
}