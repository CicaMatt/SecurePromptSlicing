#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *payload) {
    char name[BUFFER_size] = {0};
    if (sscanf(payload, "name=%[^\n]", name) == 1) {
        printf("Name: %s\n", name);
    } else {
        printf("Name not found in payload.\n");
    }
}

int main() {
    char request[BUFFER_SIZE] = 
        "GET /api HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "Content-Length: 11\r\n"
        "\r\n"
        "name=JohnDoe";

    char *method, *path, *version;
    char header[BUFFER_SIZE] = {0}, payload[BUFFER_SIZE] = {0};

    sscanf(request, "%s %s %s", method, path, version);

    if (strcmp(method, "GET") == 0 && strcmp(path, "/api") == 0) {
        const char *header_end = strstr(request, "\r\n\r\n");
        if (header_end != NULL) {
            strncpy(header, request, header_end - request);
            strcpy(payload, header_end + 4); // Skip the "\r\n\r\n"

            handle_request(payload);
        }
    } else {
        printf("Invalid request.\n");
    }

    return 0;
}