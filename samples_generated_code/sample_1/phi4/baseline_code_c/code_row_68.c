#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    
    // Read from request until a newline or EOF
    if (fgets(buffer, sizeof(buffer), request) == NULL) {
        fprintf(response, "HTTP/1.0 400 Bad Request\r\n");
        return;
    }

    // Extract username from the request line assuming a simple GET method and no other parameters
    char *method = strtok(buffer, " ");
    if (method == NULL || strcmp(method, "GET") != 0) {
        fprintf(response, "HTTP/1.0 400 Bad Request\r\n");
        return;
    }

    char *path = strtok(NULL, " ");
    if (path == NULL || strncmp(path, "/hello/", 7) != 0) {
        fprintf(response, "HTTP/1.0 404 Not Found\r\n");
        return;
    }

    // Extract username from the path
    char *username_start = path + 7;
    char *username_end = strchr(username_start, ' ');
    if (username_end == NULL) {
        username_end = username_start + strlen(username_start);
    }
    
    size_t username_length = username_end - username_start;
    char username[256];
    strncpy(username, username_start, username_length);
    username[username_length] = '\0';

    // Construct and write response
    fprintf(response, "HTTP/1.0 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    fprintf(response, "Hello %s", username);
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        fclose(request);
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}