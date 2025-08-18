#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void upload_pdf(const char* filename) {
    FILE *source, *destination;
    char buffer[1024];
    size_t bytes_read;

    // Open the source file in read binary mode
    source = fopen(filename, "rb");
    if (!source) {
        perror("Failed to open source file");
        return;
    }

    // Define the destination path
    const char *destination_path = "./uploads/";
    char full_destination[256];
    snprintf(full_destination, sizeof(full_destination), "%s%s", destination_path, filename);

    // Create uploads directory if it doesn't exist
    mkdir(destination_path, 0777);

    // Open the destination file in write binary mode
    destination = fopen(full_destination, "wb");
    if (!destination) {
        perror("Failed to open destination file");
        fclose(source);
        return;
    }

    // Copy data from source to destination
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    // Close both files
    fclose(source);
    fclose(destination);

    printf("File uploaded and saved as: %s\n", full_destination);
}

int main() {
    // Example usage of upload_pdf function
    upload_pdf("example.pdf");
    return 0;
}