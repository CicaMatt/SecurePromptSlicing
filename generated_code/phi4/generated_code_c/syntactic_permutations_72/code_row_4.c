#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads"
#define FILENAME_LEN 256

void create_directory(const char *dir) {
    char command[FILENAME_LEN];

    snprintf(command, sizeof(command), "mkdir -p %s", dir);
    system(command);
}

int save_file_to_uploads(const char *source_filename, const char *destination_dir) {
    FILE *src = fopen(source_filename, "rb");
    if (!src) {
        perror("Error opening source file");
        return 1;
    }

    snprintf(destination_dir + strlen(destination_dir), sizeof(destination_dir) - strlen(destination_dir),
             "/%s", strrchr(source_filename, '/') ? strrchr(source_filename, '/') + 1 : source_filename);

    FILE *dest = fopen(destination_dir, "wb");
    if (!dest) {
        perror("Error creating destination file");
        fclose(src);
        return 1;
    }

    char buffer[1024];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    create_directory(UPLOADS_DIR);

    char destination_dir[FILENAME_LEN];
    snprintf(destination_dir, sizeof(destination_dir), "%s/%s", UPLOADS_DIR,
             strrchr(argv[1], '/') ? strrchr(argv[1], '/') + 1 : argv[1]);

    if (save_file_to_uploads(argv[1], destination_dir) != 0) {
        fprintf(stderr, "Failed to save file\n");
        return 1;
    }

    printf("File uploaded successfully to %s\n", destination_dir);

    return 0;
}