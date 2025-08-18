#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define UPLOADS_DIR "uploads"

void createDirectoryIfNotExists(const char *dir) {
    if (access(dir, F_OK) == -1) {
        mkdir(dir, 0755);
    }
}

int savePdfFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return -1;

    createDirectoryIfNotExists(UPLOADS_DIR);

    char uploadPath[256];
    snprintf(uploadPath, sizeof(uploadPath), "%s/%s", UPLOADS_DIR, filename);

    FILE *uploadFile = fopen(uploadPath, "wb");
    if (!uploadFile) {
        fclose(file);
        return -1;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytesRead, uploadFile);
    }

    fclose(file);
    fclose(uploadFile);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <pdf_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int result = savePdfFile(filename);

    if (result == 0) {
        printf("PDF file saved successfully.\n");
    } else {
        perror("Error saving PDF file");
    }

    return result;
}