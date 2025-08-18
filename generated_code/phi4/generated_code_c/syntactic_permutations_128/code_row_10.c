#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request line by line until we find "username="
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp("GET /?username=", buffer, 16) == 0) {
            char username[128] = "";
            sscanf(buffer + 16, "%[^&\n]", username);
            
            // Construct the response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "hello %s", username);
            break;
        }
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r"); // Simulated request input
    if (request == NULL) return 1;

    FILE *response = fopen("server_response.txt", "w"); // Simulated response output
    if (response == NULL) {
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);
    
    return 0;
}