#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_REQUEST_SIZE 1024 * 1024 * 5 // 5MB max request size
#define UPLOADS_DIR "uploads"

void handle_request(char *request) {
    char method[10], path[100], protocol[10];
    sscanf(request, "%s %s %s", method, path, protocol);

    if (strcmp(method, "POST") == 0 && strcmp(path, "/upload") == 0) {
        char boundary[100];
        sscanf(request, "%*[^boundary]boundary=%[^\\r]", boundary);
        
        char *content = strstr(request, "\r\n\r\n");
        content += 4;

        char *filename_start = strstr(content, "filename=\"");
        if (filename_start == NULL) {
            printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
            return;
        }

        filename_start += 10;
        char *filename_end = strchr(filename_start, '"');
        int filename_len = filename_end - filename_start;
        char filename[filename_len + 1];
        strncpy(filename, filename_start, filename_len);
        filename[filename_len] = '\0';

        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s", UPLOADS_DIR, filename);

        content = strstr(content, "\r\n\r\n");
        content += 4;

        char *boundary_end = strstr(content, boundary);
        int file_content_len = boundary_end - content;
        char file_content[file_content_len + 1];
        strncpy(file_content, content, file_content_len);
        file_content[file_content_len] = '\0';

        FILE *file = fopen(filepath, "wb");
        if (file == NULL) {
            printf("HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n");
            return;
        }
        fwrite(file_content, 1, file_content_len, file);
        fclose(file);

        printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 46\r\n\r\n"
               "<html><body>File uploaded successfully.</body></html>");
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
    }
}

int main() {
    mkdir(UPLOADS_DIR, 0755);

    char request[MAX_REQUEST_SIZE];
    while (fgets(request, sizeof(request), stdin)) {
        handle_request(request);
    }

    return 0;
}