#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char request_line[BUFFER_SIZE];
    if (fgets(request_line, sizeof(request_line), request) == NULL) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }

    // Extract username from the request line
    char *method = strtok(request_line, " ");
    if (strcmp(method, "GET") != 0) {
        fprintf(response, "HTTP/1.1 405 Method Not Allowed\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }

    char *path = strtok(NULL, " ");
    if (strncmp(path, "/hello/", 7) != 0) {
        fprintf(response, "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }

    char *username = path + 7;
    if (*username == '\n' || *username == '\r') {
        username[0] = '\0';
    }
    
    // Construct the response
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nHello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (!request) {
        perror("Error opening request file");
        return 1;
    }

    FILE *response = fopen("response.txt", "w");
    if (!response) {
        perror("Error opening response file");
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}