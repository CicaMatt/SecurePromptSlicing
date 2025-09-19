#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    file = fopen("important_config", "w");
    if (file == NULL) {
        perror("Failed to create the file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
    return 0;
}