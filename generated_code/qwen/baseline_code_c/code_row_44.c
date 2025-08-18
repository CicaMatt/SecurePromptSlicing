#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[1024];
    char buffer[1024];

    printf("Enter the name of the file to read: ");
    scanf("%1023s", filename);

    // Constructing the full path
    char path[1024] = "/safe/";
    snprintf(path, sizeof(path), "%s%s", path, filename);

    file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return EXIT_SUCCESS;
}