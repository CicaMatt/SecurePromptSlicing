#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[256];
    char buffer[1024];

    printf("Enter the name of the file to read: ");
    scanf("%255s", filename);

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