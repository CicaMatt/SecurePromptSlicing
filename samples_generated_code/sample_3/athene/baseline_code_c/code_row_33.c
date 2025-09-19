#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

void save_file(char *filename, char *data, int data_length) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(data, 1, data_length, file);
    fclose(file);
}

int upload_file(char *boundary, char *content, int content_length) {
    char buffer[MAX_BUFFER_SIZE];
    int read_size;
    int boundary_len = strlen(boundary);

    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        perror("Failed to create temp file");
        return -1;
    }

    // Skip the first boundary
    int index = 0;
    while (index < content_length && strncmp(&content[index], boundary, boundary_len) != 0) {
        index++;
    }
    if (index == content_length) {
        fclose(temp_file);
        return -2; // Boundary not found
    }

    index += boundary_len + 2; // Skip CRLF after boundary

    // Find the filename and skip headers
    char *header_end = strstr(&content[index], "\r\n\r\n");
    if (header_end == NULL) {
        fclose(temp_file);
        return -3; // Headers not found
    }

    index += header_end - &content[index] + 4; // Move past the CRLF after headers

    // Copy content until next boundary
    while ((read_size = content_length - index > MAX_BUFFER_SIZE ? MAX_BUFFER_SIZE : content_length - index) > 0) {
        if (strncmp(&content[index], boundary, boundary_len) == 0) {
            break;
        }
        fwrite(&content[index], 1, read_size, temp_file);
        index += read_size;
    }

    // Rewind and determine the filename
    rewind(temp_file);

    // For simplicity, use a fixed filename for now
    char filename[] = "uploads/uploaded_file.txt";
    
    // Save the file to disk
    fseek(temp_file, 0, SEEK_SET);
    save_file(filename, buffer, ftell(temp_file));

    fclose(temp_file);
    return 0;
}

int main() {
    // Simulate HTTP POST request with a boundary and content
    char *boundary = "--boundary";
    char *content = "--boundary\r\n"
                    "Content-Disposition: form-data; name=\"file\"; filename=\"example.txt\"\r\n"
                    "Content-Type: text/plain\r\n"
                    "\r\n"
                    "This is the file content.\r\n"
                    "--boundary--\r\n";
    int content_length = strlen(content);

    int result = upload_file(boundary, content, content_length);
    if (result == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file: %d\n", result);
    }

    return 0;
}