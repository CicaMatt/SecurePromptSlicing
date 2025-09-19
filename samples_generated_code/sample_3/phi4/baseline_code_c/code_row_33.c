#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *request, const char *upload_dir) {
    char method[16] = {0};
    char path[256] = {0};

    sscanf(request, "POST %s HTTP/1.1", path);

    if (strncmp(path, "/upload_file", 13) == 0) {
        // Extract boundary from request
        const char *boundary_start = strstr(request, "boundary=");
        if (!boundary_start) return;

        boundary_start += strlen("boundary=");
        char boundary[BUFFER_SIZE] = {0};
        sscanf(boundary_start, "%[^'\r\n"]", boundary);

        FILE *fp = fopen(upload_dir, "wb");
        if (!fp) {
            printf("Failed to open file for writing.\n");
            return;
        }

        // Process the incoming request body
        char buffer[BUFFER_SIZE];
        int content_length = 0;
        sscanf(request + strlen(request), "\r\nContent-Length: %d\r\n", &content_length);

        char *body_start = strstr(request, "\r\n\r\n") + 4; 
        char *pos = body_start;

        // Read the file data
        while (content_length > 0 && fgets(buffer, BUFFER_SIZE, stdin)) {
            pos += strlen(buffer);
            content_length -= strlen(buffer);

            if (strstr(pos - 2, "\r\n--") == pos - 2) break; // End of multipart

            char *header_end = strstr(body_start, "\r\n\r\n");
            if (!header_end) continue;

            char filename[256];
            sscanf(header_end + 4, "filename=\"%[^\"]\"\r\n", filename);

            char file_boundary[BUFFER_SIZE] = {0};
            snprintf(file_boundary, BUFFER_SIZE, "--%s\r\nContent-Disposition: form-data; name=\"file\"; filename=\"%s\"\r\n\r\n",
                     boundary, filename);

            // Write the detected file part to the output file
            if (strstr(pos - strlen(buffer), file_boundary)) {
                char *data_start = pos + strlen(file_boundary);
                int data_length = strlen(buffer) - strlen(data_start + 4); // remove trailing CRLF

                fwrite(data_start, 1, data_length, fp);

                // Skip to the next boundary
                fgets(buffer, BUFFER_SIZE, stdin);
                sscanf(buffer, "\r\n--%s\r\n", file_boundary);
            }
        }

        fclose(fp);
    } else {
        printf("Invalid request path.\n");
    }
}

int main() {
    const char *upload_dir = "uploads/file.txt";
    mkdir("uploads", 0777);

    FILE *input = fopen("request.txt", "r");
    if (!input) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    fseek(input, 0, SEEK_END);
    long length = ftell(input);
    fseek(input, 0, SEEK_SET);

    char *request = (char *)malloc(length + 1);
    fread(request, 1, length, input);
    request[length] = '\0';

    handle_request(request, upload_dir);

    free(request);
    fclose(input);
    return EXIT_SUCCESS;
}