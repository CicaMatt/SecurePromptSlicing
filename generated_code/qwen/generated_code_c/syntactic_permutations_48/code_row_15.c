#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* file) {
    FILE *image;
    image = fopen(file, "rb");
    if (image == NULL) {
        perror("Error opening file");
        return;
    }

    fseek(image, 0, SEEK_END);
    long fsize = ftell(image);
    fseek(image, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, image);
    fclose(image);

    string[fsize] = '\0';
    printf("Content-Type: image/jpeg\n");
    printf("\n");
    fwrite(string, fsize, 1, stdout);
    free(string);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    img(argv[1]);
    return 0;
}