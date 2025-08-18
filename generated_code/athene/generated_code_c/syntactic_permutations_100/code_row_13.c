#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fclose(file);
    return EXIT_SUCCESS;
}