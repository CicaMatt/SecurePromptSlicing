#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    const char *configString = "important_config";
    if (fprintf(file, "%s", configString) < 0) {
        perror("Failed to write to file");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fclose(file);
    return 0;
}