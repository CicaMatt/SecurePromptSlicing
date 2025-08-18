#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read the request line by line until we find one starting with "GET"
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET", 3) == 0) {
            break;
        }
    }

    // Extract the username from the request
    char *username = NULL;
    if (sscanf(buffer, "GET /?username=%ms HTTP/1.1", &username) != 1 || username == NULL) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request");
        return;
    }

    // Construct the response
    char response_header[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
    fprintf(response, "%sHello %s", response_header, username);

    free(username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("response.txt", "w");
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