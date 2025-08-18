#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fprintf(file, "important_config");
    fclose(file);
    return 0;
}