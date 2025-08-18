#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define UPLOAD_DIR "uploads"

void handle_request(const char *filename, const char *filecontent) {
    mkdir(UPLOAD_DIR, 0777);
    
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

    FILE *file = fopen(filepath, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    fwrite(filecontent, 1, strlen(filecontent), file);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <filecontent>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    const char *filecontent = argv[2];

    handle_request(filename, filecontent);

    printf("File uploaded successfully to %s/%s\n", UPLOAD_DIR, filename);
    return EXIT_SUCCESS;
}