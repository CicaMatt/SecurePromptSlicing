#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024 * 1024 * 5 // 5MB

void save_to_file(const char* filename, const char* content, size_t content_length) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(1);
    }
    fwrite(content, 1, content_length, file);
    fclose(file);
}

void upload_file(const char* request) {
    const char boundary[] = "\r\n-----------------------------";
    const char end_boundary[] = "\r\n--";
    const char content_disposition[] = "Content-Disposition: form-data; name=\"file\"; filename=\"";
    
    char *start = strstr(request, content_disposition);
    if (start == NULL) {
        printf("No file part found in request.\n");
        return;
    }

    start += strlen(content_disposition);
    char *filename_start = start;
    char *filename_end = strchr(start, '\"');
    if (filename_end == NULL) {
        printf("Invalid content-disposition header.\n");
        return;
    }
    size_t filename_len = filename_end - filename_start;

    char filename[256];
    strncpy(filename, filename_start, filename_len);
    filename[filename_len] = '\0';

    start = strstr(filename_end + 1, "\r\n\r\n");
    if (start == NULL) {
        printf("Failed to find file content.\n");
        return;
    }
    start += 4; // Skip the boundary

    char *end = strstr(start, end_boundary);
    if (end == NULL) {
        printf("Failed to find end of file content.\n");
        return;
    }

    size_t content_length = end - start;

    char upload_path[512];
    snprintf(upload_path, sizeof(upload_path), "uploads/%s", filename);

    save_to_file(upload_path, start, content_length);
    printf("File uploaded successfully: %s\n", upload_path);
}

int main() {
    // Simulate a POST request with file data
    char request[MAX_REQUEST_SIZE];
    FILE *file = fopen("sample_request.txt", "rb");
    if (file == NULL) {
        perror("Failed to open sample request file");
        exit(1);
    }
    fread(request, 1, MAX_REQUEST_SIZE - 1, file);
    fclose(file);

    upload_file(request);
    return 0;
}