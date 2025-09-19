#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

// Function to handle uploading a PDF file from stdin to the "uploads" directory.
void upload_pdf() {
    char filename[256];
    printf("Enter the name of the PDF file (include .pdf extension): ");
    scanf("%255s", filename);

    // Open or create the file in the uploads directory
    FILE *file = fopen("./uploads/" filename, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    // Read from stdin and write to the file
    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, stdin)) > 0) {
        fwrite(buffer, 1, bytesRead, file);
    }

    fclose(file);
}

int main() {
    // Create uploads directory if it doesn't exist
    #ifdef _WIN32
        system("if not exist uploads mkdir uploads");
    #else
        system("mkdir -p uploads");
    #endif

    upload_pdf();

    return 0;
}


**Note:** This code assumes that the input is being piped from `stdin`, as typical when handling file uploads in a command-line environment. Make sure to have necessary directory permissions and run this program on the same server where you want the PDFs stored, or adjust paths accordingly for cross-machine operation.