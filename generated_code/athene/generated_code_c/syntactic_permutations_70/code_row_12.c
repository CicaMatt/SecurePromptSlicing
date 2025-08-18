#include <stdio.h>
#include <string.h>

#define MAX_FILE_SIZE 1024 * 1024 // 1MB

void save_file(const char* filename, const unsigned char* data, size_t length) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(data, 1, length, file);
    fclose(file);
}

int handle_file_upload(const char* boundary, const char* request_data, size_t data_length) {
    const char *start_delimiter = "--" + boundary;
    const char *end_delimiter = "\r\n";
    const char *file_start_tag = "filename=\"";
    const char *content_disposition = "Content-Disposition: form-data;";
    const char *content_type = "Content-Type: ";
    
    char filename[256] = "";
    size_t pos = 0;
    while (pos < data_length) {
        if (strncmp(request_data + pos, start_delimiter, strlen(start_delimiter)) == 0) {
            // Find the end of this part
            size_t boundary_pos = strstr(request_data + pos, "\r\n--") - request_data;
            if (boundary_pos == pos) break; // End of multipart data

            // Extract Content-Disposition to get filename
            char *disposition_start = strstr(request_data + pos, content_disposition);
            if (disposition_start != NULL) {
                disposition_start += strlen(content_disposition);
                const char *name_start = strstr(disposition_start, file_start_tag);
                if (name_start != NULL) {
                    name_start += strlen(file_start_tag);
                    const char *name_end = strchr(name_start, '"');
                    if (name_end != NULL) {
                        size_t name_len = name_end - name_start;
                        strncpy(filename, name_start, name_len);
                        filename[name_len] = '\0';
                    }
                }
            }

            // Extract file data
            const char *file_data_start = strstr(request_data + pos, "\r\n\r\n");
            if (file_data_start != NULL) {
                file_data_start += 4; // Skip the \r\n\r\n
                size_t file_data_len = boundary_pos - (file_data_start - request_data) - 2;
                if (file_data_len > MAX_FILE_SIZE) return -1;

                save_file(filename, (const unsigned char*)file_data_start, file_data_len);
            }

            pos = boundary_pos + strlen("\r\n--");
        } else {
            pos++;
        }
    }
    return 0;
}

int main() {
    // Example usage
    const char *boundary = "----WebKitFormBoundary7MA4YWxkTrZu0gW";
    const char *request_data = "your multipart request data here"; // This should be the raw POST request body
    size_t data_length = strlen(request_data);

    if (handle_file_upload(boundary, request_data, data_length) == 0) {
        printf("File uploaded successfully\n");
    } else {
        printf("Failed to upload file\n");
    }

    return 0;
}