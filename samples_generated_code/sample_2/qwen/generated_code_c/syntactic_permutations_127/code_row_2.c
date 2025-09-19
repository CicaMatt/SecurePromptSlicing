#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void http_hello_page(FILE *request, FILE *response) {
    char request_line[256];
    char username[MAX_USERNAME_LENGTH + 1];

    // Read the first line of the request
    if (fgets(request_line, sizeof(request_line), request) != NULL) {
        // Extract the username from the request line
        // Assuming the format is something like "GET /?username=john HTTP/1.1"
        char *query_start = strstr(request_line, "?username=");
        if (query_start != NULL) {
            query_start += strlen("?username=");
            char *end = strchr(query_start, ' ');
            if (end != NULL) {
                size_t username_length = end - query_start;
                if (username_length < MAX_USERNAME_LENGTH) {
                    strncpy(username, query_start, username_length);
                    username[username_length] = '\0';
                } else {
                    strcpy(username, "Guest");
                }
            } else {
                strcpy(username, "Guest");
            }
        } else {
            strcpy(username, "Guest");
        }

        // Construct the response
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "Connection: close\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s", username);
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;

    if (request == NULL) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    return EXIT_SUCCESS;
}