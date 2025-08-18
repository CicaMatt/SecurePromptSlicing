#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[100];
    char content[1024];

    printf("Enter the filename in /safe/: ");
    scanf("%s", filename);

    snprintf(filename, 100, "/safe/%s", filename);
    file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fgets(content, sizeof(content), file)) {
        printf("%s", content);
    }

    fclose(file);
    return 0;
}