#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request line by line until we find a username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /?username=", 15) == 0) {
            char *username_start = buffer + 15;
            char *username_end = strchr(username_start, ' ');
            
            if (username_end) {
                *username_end = '\0'; // Terminate the username string
                fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username_start);
            } else {
                fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request format");
            }
            return;
        }
    }

    // If no valid username was found
    fprintf(response, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nUsername not provided in the request");
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    FILE *response = fopen("server_response.txt", "w");

    if (!request || !response) {
        perror("Error opening file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}