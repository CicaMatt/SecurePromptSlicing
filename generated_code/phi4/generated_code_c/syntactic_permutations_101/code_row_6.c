#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("config.txt", "w");
    
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *important_config = "This is important configuration data.";

    if (fprintf(file, "%s\n", important_config) < 0) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fclose(file);
    return EXIT_SUCCESS;
}