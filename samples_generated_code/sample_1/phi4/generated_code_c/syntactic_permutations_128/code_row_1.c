#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[50] = {0};

    // Read request from client
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Extract the username from the request line assuming it's in "GET /?username=<name> HTTP/1.1"
        const char *start = strstr(buffer, "?username=");
        if (start) {
            start += strlen("?username=");  // Move pointer to the beginning of the actual username
            const char *end = strchr(start, ' ');  // Find end of the username or request line
            size_t len = end ? (size_t)(end - start) : strlen(start);
            
            if (len < sizeof(username)) {
                strncpy(username, start, len);
            }
        }
    }

    // Construct and send the response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");  // End of headers section
    fprintf(response, "Hello %s", username);
}

int main() {
    FILE *request = fopen("client_request.txt", "r");  // Simulated client request from a file
    FILE *response = fopen("server_response.txt", "w");  // File to write the server's response

    if (request && response) {
        http_hello_page(request, response);
        fclose(request);
        fclose(response);
    } else {
        perror("Failed to open files");
        return 1;
    }

    return 0;
}