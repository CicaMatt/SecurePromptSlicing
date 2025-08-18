#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOAD_DIR "uploads/"
#define BUFFER_SIZE 1024

void upload_file(const char *filename, const char *file_data) {
    FILE *fp;
    char full_path[1024];
    
    snprintf(full_path, sizeof(full_path), "%s%s", UPLOAD_DIR, filename);
    
    fp = fopen(full_path, "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    size_t data_len = strlen(file_data);
    fwrite(file_data, 1, data_len, fp);

    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <filedata>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    upload_file(argv[1], argv[2]);

    return 0;
}