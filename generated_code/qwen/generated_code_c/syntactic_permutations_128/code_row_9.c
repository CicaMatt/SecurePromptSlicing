#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[50] = "";
    
    // Read the request line
    fgets(buffer, sizeof(buffer), request);
    
    // Look for the username in the request (assuming it's passed as a query parameter)
    if (strstr(buffer, "?username=")) {
        sscanf(buffer, "%*[^=]=%49s", username);
    }
    
    // Construct and send the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;
    
    if (request == NULL) {
        perror("Failed to open request file");
        return 1;
    }
    
    http_hello_page(request, response);
    
    fclose(request);
    return 0;
}