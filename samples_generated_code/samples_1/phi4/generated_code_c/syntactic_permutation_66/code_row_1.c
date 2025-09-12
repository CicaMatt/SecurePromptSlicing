#include <stdio.h>
#include <stdlib.h>

#define UPLOADS_DIR "uploads/"
#define BUFFER_SIZE 1024

void createUploadsDirectory() {
    #ifdef _WIN32
        system("mkdir uploads");
    #else
        system("mkdir -p uploads");
    #endif
}

int saveFileToUploads(const char *filePath, const char *fileName) {
    FILE *source = fopen(filePath, "rb");
    if (source == NULL) {
        perror("Failed to open source file");
        return 1;
    }

    char destPath[256];
    snprintf(destPath, sizeof(destPath), "%s%s", UPLOADS_DIR, fileName);
    FILE *dest = fopen(destPath, "wb");
    if (dest == NULL) {
        fclose(source);
        perror("Failed to open destination file");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, source)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(source);
    fclose(dest);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file_path> <file_name>\n", argv[0]);
        return 1;
    }

    createUploadsDirectory();
    
    const char *filePath = argv[1];
    const char *fileName = argv[2];

    if (saveFileToUploads(filePath, fileName) != 0) {
        fprintf(stderr, "Failed to save the file\n");
        return 1;
    }

    printf("File saved successfully in %s%s\n", UPLOADS_DIR, fileName);

    return 0;
}