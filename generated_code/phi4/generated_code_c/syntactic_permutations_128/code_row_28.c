#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request from the file stream
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        const char *username = "unknown";
        
        // Extract username from request; assuming it's in a simple format like "GET /?user=USERNAME HTTP/1.1"
        for (const char *p = buffer; *p; p++) {
            if (*p == '?') {
                p += 6; // Skip "?user="
                while (*p && *p != ' ') username = p;
                break;
            }
        }

        // Construct the response
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s!\n", username);
    } else {
        fprintf(stderr, "Failed to read request.\n");
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Failed to open client request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        perror("Failed to open server response file");
        fclose(request);
        return EXIT_FAILURE;
    }
    
    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}