#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("example.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    const char *str = "Hello, World!";
    fprintf(file, "%s", str);
    fclose(file);
    return 0;
}