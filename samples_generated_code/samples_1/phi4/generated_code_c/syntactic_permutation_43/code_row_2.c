#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "/safe/example.txt"; // Specify your file name here
    char buffer[256];

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}