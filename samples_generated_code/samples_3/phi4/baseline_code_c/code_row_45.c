#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = {0};

    // Read the request line (assuming a simple GET method and ignoring headers for simplicity)
    if (fgets(buffer, sizeof(buffer), request)) {
        // Extracting username from path assuming URL format: /hello?username=<name>
        const char *prefix = "/hello?username=";
        char *start = strstr(buffer, prefix);
        
        if (start) {
            start += strlen(prefix);  // Move the pointer to the beginning of the username
            sscanf(start, "%255s", username);  // Read up to 255 characters into username
        }
    }

    // Construct and write response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");  // End of headers section
    fprintf(response, "hello %s", username);
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) return 1;

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}