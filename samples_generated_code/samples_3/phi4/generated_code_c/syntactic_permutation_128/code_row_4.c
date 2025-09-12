#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char line[1024];
    
    // Read the request line (assuming only one line for simplicity)
    if (fgets(line, sizeof(line), request) == NULL) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }
    
    // Parse the username from a simple GET request
    char *method = strtok(line, " ");
    if (strcmp(method, "GET") != 0) {
        fprintf(response, "HTTP/1.1 405 Method Not Allowed\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }

    char *path = strtok(NULL, " ");
    if (path == NULL || strncmp(path, "/hello/", 7) != 0) {
        fprintf(response, "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }

    char *username = path + 7; // Skip the /hello/
    if (*username == '\r' || *username == ' ') { // Check for empty username
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }

    // Construct response
    char responseBuffer[1024];
    snprintf(responseBuffer, sizeof(responseBuffer),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/plain\r\n"
             "Content-Length: %zu\r\n"
             "Connection: close\r\n"
             "\r\n"
             "Hello %s",
             strlen("Hello ") + strlen(username), username);

    // Write response
    fputs(responseBuffer, response);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Error opening files");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}