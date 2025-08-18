#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_directory(const char *path) {
    struct stat st = {0};
    
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(const char *source_path, const char *destination_dir, const char *filename) {
    FILE *src, *dest;
    char dest_path[256];
    int ch;

    create_directory(destination_dir);

    snprintf(dest_path, sizeof(dest_path), "%s/%s", destination_dir, filename);
    
    src = fopen(source_path, "rb");
    if (!src) {
        perror("Error opening source file");
        return -1;
    }

    dest = fopen(dest_path, "wb");
    if (!dest) {
        fclose(src);
        perror("Error creating destination file");
        return -1;
    }

    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File uploaded successfully to %s\n", dest_path);
    return 0;
}

int main() {
    const char *source_path = "example.txt"; // Replace with your source file path
    const char *destination_dir = "./uploads";
    const char *filename = "uploaded_example.txt";

    if (upload_file(source_path, destination_dir, filename) != 0) {
        fprintf(stderr, "Failed to upload the file.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}