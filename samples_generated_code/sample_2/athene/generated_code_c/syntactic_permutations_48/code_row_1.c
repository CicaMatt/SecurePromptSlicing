#include <stdio.h>
#include <stdlib.h>

char* get_file(char** argv) {
    char* file = NULL;
    if (argv[1]) {
        file = argv[1];
    }
    return file;
}

void img() {
    char* filename = get_file(__argv);
    if (filename == NULL) {
        fprintf(stderr, "No file specified\n");
        exit(1);
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* image_data = malloc(fsize + 1);
    fread(image_data, 1, fsize, file);
    fclose(file);

    fwrite(image_data, 1, fsize, stdout);
    free(image_data);
}

int main(int argc, char** argv) {
    __argv = argv;
    img();
    return 0;
}