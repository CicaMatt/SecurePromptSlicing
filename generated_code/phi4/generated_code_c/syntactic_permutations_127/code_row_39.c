#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Move to the start of the request stream if needed (assuming username is at the beginning)
    rewind(request);

    // Read the username from the request file stream
    fgets(buffer, sizeof(buffer), request);
    
    // Construct and send the response
    fprintf(response, "Hello %s", buffer);
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Failed to open client request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        fclose(request);
        perror("Failed to open server response file");
        return EXIT_FAILURE;
    }
    
    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}