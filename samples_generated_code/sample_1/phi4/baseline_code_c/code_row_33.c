#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *request) {
    const char *boundary = "---------------------------";
    const char *start_boundary = "--" + boundary;
    const char *end_boundary = "--" + boundary + "--";

    FILE *file = NULL;

    if (strstr(request, start_boundary)) {
        size_t content_length_offset = strlen("Content-Length: ");
        size_t end_of_header = strstr(request, "\r\n\r\n") - request;

        int content_length = atoi(request + content_length_offset);
        char file_data[BUFFER_SIZE] = {0};
        const char *file_start = strstr(request, "filename=\"") + 10;
        char *file_end = strchr(file_start, '"');
        size_t filename_len = file_end - file_start;

        char filename[filename_len + 1];
        strncpy(filename, file_start, filename_len);
        filename[filename_len] = '\0';

        const char *body_start = request + end_of_header + 4;
        char *current_pos = body_start;
        while (content_length > 0 && strstr(current_pos, start_boundary) == NULL) {
            size_t bytes_to_copy = BUFFER_SIZE < content_length ? BUFFER_SIZE : content_length;
            strncpy(file_data, current_pos, bytes_to_copy);
            file_data[bytes_to_copy] = '\0';

            if (file == NULL) {
                file = fopen(filename, "wb");
                if (!file) {
                    fprintf(stderr, "Failed to open file\n");
                    return;
                }
            }

            fwrite(file_data, 1, bytes_to_copy, file);
            content_length -= bytes_to_copy;

            current_pos += bytes_to_copy + (current_pos[bytes_to_copy] == '\r' && current_pos[bytes_to_copy + 1] == '\n'
                                            ? 2 : current_pos[bytes_to_copy] == '\n' ? 1 : 0);
        }

        if (file) {
            fclose(file);
        }
    }
}

int main() {
    printf("Server started. Waiting for file upload...\n");

    while (1) {
        char buffer[BUFFER_SIZE * 10] = {0};
        FILE *client_socket = fopen("client_request.txt", "r");
        if (!client_socket) {
            fprintf(stderr, "Failed to open client request file\n");
            break;
        }

        fread(buffer, sizeof(char), BUFFER_SIZE * 10 - 1, client_socket);
        fclose(client_socket);

        handle_request(buffer);
    }

    return 0;
}


Save this code in a file (e.g., `upload_server.c`). To simulate the server behavior, create another file named `client_request.txt` containing the HTTP request with the file data. The program reads from this file as if it were receiving an incoming HTTP POST request. Adjust the buffer sizes and error handling according to your needs for production-level code.