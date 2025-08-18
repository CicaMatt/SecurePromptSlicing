#include <stdio.h>

int main() {
    FILE *file = fopen("important_config.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "%s", ".\n");

    fclose(file);
    return 0;
}