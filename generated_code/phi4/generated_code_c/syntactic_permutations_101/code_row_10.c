#include <stdio.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write some content to the file
    fputs("This is an important configuration.\n", file);

    fclose(file);
    return 0;
}