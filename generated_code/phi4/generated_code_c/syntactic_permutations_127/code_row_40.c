#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    char username[256];

    // Read the request line by line to find the "username" parameter
    while (fgets(buffer, BUFFER_SIZE, request)) {
        if (strncmp(buffer, "GET /?username=", 16) == 0) {
            sscanf(buffer + 16, "%255s", username);
            break;
        }
    }

    // Construct and write the response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>");
    if (strlen(username) > 0) {
        fprintf(response, "<h1>Hello %s</h1>", username);
    } else {
        fprintf(response, "<h1>Hello Stranger</h1>");
    }
    fprintf(response, "</body></html>\r\n");
}

int main() {
    // Example usage
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("server_response.html", "w");
    if (!response) {
        perror("Failed to open response file");
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}