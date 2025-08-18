#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read the request line from the client
    if (fgets(buffer, sizeof(buffer), request) == NULL) {
        fprintf(stderr, "Error reading request\n");
        return;
    }

    // Parse the username from the request
    char *username = strstr(buffer, "username=");
    if (!username || sscanf(username + 9, "%[^&]", buffer) != 1) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }

    // Construct the response
    char response_header[] = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain; charset=UTF-8\r\n"
        "Connection: close\r\n"
        "\r\n";
    
    fprintf(response, "%s", response_header);
    fprintf(response, "hello %s", buffer);
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        fclose(request);
        perror("Failed to open response file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}