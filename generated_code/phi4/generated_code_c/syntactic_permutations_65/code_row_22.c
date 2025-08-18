#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_URL "http://example.com/upload"  // Replace with actual server URL

// Function prototypes
void createUploadDirectory();
void uploadFile(const char *filePath);

int main() {
    const char *pdfFilePath = "./uploads/sample.pdf";  // Example file path, replace as needed
    
    createUploadDirectory();
    
    if (access(pdfFilePath, F_OK) == -1) {
        fprintf(stderr, "Error: File does not exist.\n");
        return EXIT_FAILURE;
    }
    
    uploadFile(pdfFilePath);
    
    return EXIT_SUCCESS;
}

void createUploadDirectory() {
    const char *dirPath = "./uploads";
    struct stat st = {0};

    if (stat(dirPath, &st) == -1) {
        mkdir(dirPath, 0700); // Create directory with appropriate permissions
    }
}

void uploadFile(const char *filePath) {
    FILE *file;
    const char *commandFormat = "curl -F 'file=@%s' %s"; // Use curl for file upload

    file = fopen(filePath, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char command[1024];
    snprintf(command, sizeof(command), commandFormat, filePath, SERVER_URL);

    int result = system(command);  // Execute the curl command
    if (result != 0) {
        fprintf(stderr, "Error: Failed to upload file.\n");
    } else {
        printf("File uploaded successfully.\n");
    }

    fclose(file);
}


**Note:** This code uses `curl` for HTTP uploads. Ensure `curl` is installed and accessible from your system's PATH. Replace `http://example.com/upload` with the actual server URL where you intend to upload the file.