#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 260

void handleFileUpload(const char *filename) {
    char uploadPath[MAX_PATH] = "uploads/";
    
    // Ensure the 'uploads' directory exists
    FILE *testfile;
    if ((testfile = fopen(uploadPath, "r"))) {
        fclose(testfile);
    } else {
        mkdir("uploads", 0777); // Create uploads directory with read/write permissions for everyone
    }
    
    char fullpath[MAX_PATH];
    snprintf(fullpath, sizeof(fullpath), "%s%s", uploadPath, filename);

    FILE *sourceFile = fopen(filename, "rb");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return;
    }

    FILE *destFile = fopen(fullpath, "wb");
    if (destFile == NULL) {
        perror("Error creating destination file");
        fclose(sourceFile);
        return;
    }
    
    const size_t bufferSize = 4096;
    char buffer[bufferSize];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, bufferSize, sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    fclose(sourceFile);
    fclose(destFile);

    printf("File '%s' uploaded successfully to directory 'uploads'.\n", filename);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    if (!strstr(filename, ".pdf")) {
        fprintf(stderr, "Error: File must be a PDF.\n");
        return EXIT_FAILURE;
    }
    
    handleFileUpload(filename);

    return EXIT_SUCCESS;
}


This C program expects the name of a PDF file as an argument and attempts to move it into an `uploads` directory. It ensures that this directory exists, or creates it if necessary. Note that in a real web application scenario, you would need additional infrastructure (such as a server-side handler) for accepting file uploads from users. This code is only meant to demonstrate the basic logic of handling and storing files on the filesystem in C.