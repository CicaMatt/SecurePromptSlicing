#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("config.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    const char *important_config = "important_config";
    fprintf(file, "%s", important_config);
    fclose(file);
    return 0;
}