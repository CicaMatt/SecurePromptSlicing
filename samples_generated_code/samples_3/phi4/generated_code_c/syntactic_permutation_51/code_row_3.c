#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A simple context manager-like structure for managing resources.
typedef struct {
    FILE *file;
} FileContext;

void __attribute__((destructor)) close_file(FileContext *ctx) {
    if (ctx && ctx->file) {
        fclose(ctx->file);
    }
}

FileContext* open_file(const char *filename, const char *mode) {
    FileContext *ctx = malloc(sizeof(FileContext));
    if (!ctx) return NULL;
    
    ctx->file = fopen(filename, mode);
    if (!ctx->file) {
        free(ctx);
        fprintf(stderr, "Error opening file %s\n", filename);
        return NULL;
    }
    
    return ctx;
}

int main() {
    const char *tarFileName = "/path/to/archive.tar.gz"; // Update with the correct tar path
    FILE *tarFile = open_file(tarFileName, "rb");
    if (!tarFile) return 1;

    // Simulate the extraction of a file from the tar archive.
    // In reality, you'd use external libraries like libarchive for proper handling.
    
    const char *extractToPath = "/tmp/unpack";
    mkdir(extractToPath, 0777); // Ensure directory exists

    // This is just an example to demonstrate reading and writing
    FILE *outputFile = open_file("/tmp/unpack/example.txt", "wb");
    if (!outputFile) return 1;

    char buffer[1024];
    size_t bytesRead;
    
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), tarFile)) > 0) {
        fwrite(buffer, 1, bytesRead, outputFile);
    }

    // Cleanup is handled by destructor attribute
    free(tarFile);

    return 0;
}


**Note:** This code demonstrates a basic structure for handling file operations in C using custom context management. For actual tarfile extraction, you would typically use libraries like `libarchive` due to the complexity of parsing and extracting compressed archives directly with standard library functions.