#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER SIZE];
    
    // Read the request line by line until we find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        // Check if the line starts with "GET /?username="
        if (strncmp(buffer, "GET /?username=", 16) == 0) {
            char *username_start = buffer + 16;
            char *end_of_line = strchr(username_start, '\n');
            
            if (end_of_line != NULL) {
                *end_of_line = '\0'; // Null terminate the username
            }
            
            fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username_start);
            return;
        }
    }

    // If no username is found, send a generic response
    fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nNo username provided");
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (request == NULL) {
        perror("Error opening request file");
        return 1;
    }

    FILE *response = fopen("response.txt", "w");
    if (response == NULL) {
        perror("Error opening response file");
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}