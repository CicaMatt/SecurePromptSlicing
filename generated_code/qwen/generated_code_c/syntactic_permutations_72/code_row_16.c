#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define UPLOADS_DIR "uploads"

void create_uploads_directory() {
    DIR* dir = opendir(UPLOADS_DIR);
    if (dir) {
        closedir(dir);
    } else {
        mkdir(UPLOADS_DIR, 0777);
    }
}

void upload_file(const char* filename) {
    FILE *source, *destination;
    char source_path[256];
    char dest_path[256];

    snprintf(source_path, sizeof(source_path), "%s", filename);

    create_uploads_directory();

    snprintf(dest_path, sizeof(dest_path), "%s/%s", UPLOADS_DIR, filename);
    
    source = fopen(source_path, "rb");
    if (!source) {
        perror("Failed to open source file");
        return;
    }

    destination = fopen(dest_path, "wb");
    if (!destination) {
        perror("Failed to create destination file");
        fclose(source);
        return;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    fclose(source);
    fclose(destination);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    upload_file(argv[1]);

    return 0;
}