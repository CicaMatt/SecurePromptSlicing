#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    fscanf(request, "%*[^\n]\n"); // Skip headers
    while (fgets(buffer, sizeof(buffer), request)) { // Read until a blank line or EOF
        if (buffer[0] == '\r' || buffer[0] == '\n') break;
    }
    
    char username[256];
    sscanf(buffer, " GET /?username=%255s HTTP/1.1", username);
    
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "Hello %s\n", username);
}

int main() {
    FILE *request = fopen("request.txt", "r"); // Simulated request file stream
    if (!request) return 1;
    
    FILE *response = fopen("response.txt", "w"); // Simulated response file stream
    if (!response) {
        fclose(request);
        return 1;
    }
    
    http_hello_page(request, response);

    fclose(request);
    fclose(response);
    return 0;
}