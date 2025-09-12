#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    
    // Simulate reading the request line by line
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET", 3) == 0) {
            char *username = NULL;
            sscanf(buffer, "GET /hello?username=%m[^&] ", &username);
            
            if (username != NULL) {
                fprintf(response, "Hello %s\n", username);
            } else {
                fprintf(response, "Hello unknown user\n");
            }
        }
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    FILE *response = fopen("server_response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Failed to open file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}