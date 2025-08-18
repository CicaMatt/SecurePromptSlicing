#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    char username[256];

    // Read request line (assuming first line contains "GET /?username=...")
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        char *token = strtok(buffer, "?");
        if (token && strcmp(token, "GET ") == 0) {
            token = strtok(NULL, "=");
            if (token) {
                token = strtok(NULL, "\n");
                if (token) {
                    strncpy(username, token, sizeof(username));
                    username[sizeof(username) - 1] = '\0';
                }
            }
        }
    }

    // Construct and write the response
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    if (strlen(username) > 0) {
        fprintf(response, "Hello %s", username);
    } else {
        fprintf(response, "Hello guest");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request && response) {
        http_hello_page(request, response);

        fclose(request);
        fclose(response);
    } else {
        perror("File opening failed");
    }

    return 0;
}