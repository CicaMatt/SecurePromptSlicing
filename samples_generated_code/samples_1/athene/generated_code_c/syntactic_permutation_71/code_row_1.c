#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void handle_request(char *request) {
    char method[10];
    char uri[MAX_REQUEST_SIZE];
    sscanf(request, "%s %s", method, uri);

    if (strcmp(method, "POST") == 0 && strcmp(uri, "/upload") == 0) {
        FILE *file = fopen("uploaded_file", "wb");
        if (file == NULL) {
            printf("HTTP/1.1 500 Internal Server Error\r\nContent-Length: 23\r\n\r\nFailed to save file.");
            return;
        }

        char *content_disposition = strstr(request, "Content-Disposition:");
        if (content_disposition == NULL) {
            fclose(file);
            printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 35\r\n\r\nNo Content-Disposition header found.");
            return;
        }

        char *file_content = strstr(content_disposition, "\r\n\r\n");
        if (file_content == NULL) {
            fclose(file);
            printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 36\r\n\r\nNo file content found in request.");
            return;
        }

        file_content += 4; // Skip "\r\n\r\n"
        fwrite(file_content, strlen(file_content), 1, file);
        fclose(file);

        printf("HTTP/1.1 200 OK\r\nContent-Length: 36\r\n\r\nFile uploaded successfully.");
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 37\r\n\r\nEndpoint not found or method not allowed.");
    }
}

int main() {
    char request[MAX_REQUEST_SIZE];
    fgets(request, MAX_REQUEST_SIZE, stdin);

    handle_request(request);

    return 0;
}