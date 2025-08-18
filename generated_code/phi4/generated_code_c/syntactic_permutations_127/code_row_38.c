#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the username from the request
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Find the username part in the request line
        char *username_start = strstr(buffer, "username=");
        if (username_start) {
            username_start += 9; // Move past "username="
            
            // Null-terminate at the first space or newline after the username
            char *end = strchr(username_start, ' ');
            if (!end) end = strchr(username_start, '\n');
            if (end) *end = '\0';
            
            // Construct the response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s", username_start);
        }
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    FILE *response = fopen("server_response.txt", "w");

    if (request && response) {
        http_hello_page(request, response);

        fclose(request);
        fclose(response);
    }

    return 0;
}