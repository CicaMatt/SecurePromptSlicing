#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File not found\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, file);
    fclose(file);

    string[fsize] = 0;
    printf("%s\n", string);

    free(string);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    img(argv[1]);
    return 0;
}