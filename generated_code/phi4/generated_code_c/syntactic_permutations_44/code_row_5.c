#include <stdio.h>
#include <stdlib.h>

#define FILE_PATH "/safe/requested_file.txt"

int main() {
    FILE *file = fopen(FILE_PATH, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}