#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

void handle_http_request(const char *request, const char *file_path);

int main() {
    FILE *file = fopen("client_request.txt", "r");
    if (!file) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *request = (char *)malloc(length + 1);
    if (!request) {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }

    fread(request, 1, length, file);
    request[length] = '\0';

    fclose(file);

    handle_http_request(request, "uploads/uploaded_file.pdf");

    free(request);

    return EXIT_SUCCESS;
}

void handle_http_request(const char *request, const char *file_path) {
    char content_disposition[256];
    snprintf(content_disposition, sizeof(content_disposition), "Content-Disposition: form-data; name=\"file\"; filename=\"%s\"", file_path);

    if (strstr(request, content_disposition)) {
        FILE *out = fopen(file_path, "wb");
        if (!out) {
            perror("Failed to open output file");
            return;
        }

        const char *boundary_marker = strstr(request, "\r\n") + 2;
        boundary_marker = strstr(boundary_marker, "\r\n") + 2;

        while (strstr(boundary_marker, "Content-Type: application/pdf")) {
            boundary_marker = strstr(boundary_marker, "--") + 2;
            const char *end_boundary = strstr(boundary_marker, "\r\n--");
            if (!end_boundary) break;

            size_t content_length = end_boundary - boundary_marker;
            char *content = (char *)malloc(content_length);
            if (!content) {
                perror("Memory allocation failed");
                fclose(out);
                return;
            }

            strncpy(content, boundary_marker, content_length);
            content[content_length] = '\0';

            const char *data_start = strstr(content, "\r\n\r\n") + 4;
            size_t data_len = strlen(data_start);

            fwrite(data_start, 1, data_len, out);
            free(content);

            if (end_boundary == strstr(boundary_marker, "--")) break;

            boundary_marker = end_boundary;
        }

        fclose(out);
    }
}
