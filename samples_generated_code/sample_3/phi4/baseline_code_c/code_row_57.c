#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read the request line until a newline character is found or buffer limit
    if (fgets(buffer, BUFFER_SIZE, request) != NULL) {
        // Parse the username assuming it's in the format "GET /username HTTP/1.1"
        char *method = strtok(buffer, " ");
        char *path = strtok(NULL, " ");
        
        if (strcmp(method, "GET") == 0 && path[0] == '/') {
            char *username = path + 1; // Skip the leading '/'
            char response_message[BUFFER_SIZE];
            
            snprintf(response_message, sizeof(response_message), 
                     "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);
            
            fprintf(response, "%s", response_message);
        }
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    FILE *response = fopen("server_response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Error opening file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}