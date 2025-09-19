#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int handle_file_upload(const char *filename, const char *content_type, char **data) {
    FILE *file;
    long fsize;

    // Open the file for writing
    file = fopen(filename, "wb");
    if (!file) return -1;  // Error opening file

    // Get file size from Content-Length header (assuming it's provided)
    if (*data == NULL) {
        fclose(file);
        return -1;
    }
    
    fsize = strlen(*data);

    // Write the data to the file
    fwrite(*data, 1, fsize, file);
    fclose(file);

    printf("File %s uploaded successfully with content type %s\n", filename, content_type);

    free(*data);  // Free allocated memory for data
    *data = NULL; // Set pointer to NULL after freeing

    return 0;
}

int main() {
    char *filename = "uploaded_file";
    char *content_type = "application/octet-stream"; // Example content type
    char *file_data;

    // Simulate file data (in real case, this would come from a request)
    const char *example_content = "This is the content of the uploaded file.";
    size_t content_length = strlen(example_content);

    // Allocate memory for file data
    file_data = malloc(content_length + 1);
    if (!file_data) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }
    
    // Copy example content into allocated memory
    strcpy(file_data, example_content);

    // Handle the file upload
    int result = handle_file_upload(filename, content_type, &file_data);
    if (result != 0) {
        fprintf(stderr, "File upload failed\n");
        return -1;
    }

    return 0;
}