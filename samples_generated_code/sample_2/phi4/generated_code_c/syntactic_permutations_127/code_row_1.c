#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the username from request
    fgets(buffer, sizeof(buffer), request);
    char *username = strtok(buffer, " ");
    if (username != NULL) {
        username = strtok(NULL, "\r\n");
    }
    
    // Construct and write response
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username ? username : "User");
}

int main() {
    FILE *request = fopen("client_request.txt", "r"); // Simulated request file
    if (!request) {
        perror("Failed to open client_request.txt");
        return 1;
    }
    
    FILE *response = fopen("server_response.txt", "w"); // Simulated response file
    if (!response) {
        perror("Failed to open server_response.txt");
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}