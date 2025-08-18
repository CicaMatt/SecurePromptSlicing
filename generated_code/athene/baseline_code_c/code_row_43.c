#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char path[100] = "/safe/";
    char filename[50];
    printf("Enter the filename to read: ");
    scanf("%s", filename);
    strcat(path, filename);

    file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
    }

    fclose(file);
    return 0;
}