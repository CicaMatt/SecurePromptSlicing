#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read the request to find the username
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        char *username = strtok(buffer, " ");
        while (username != NULL) {
            if (strncmp(username, "GET /?username=", 16) == 0) {
                username += 16;
                break;
            }
            username = strtok(NULL, " ");
        }

        // Construct the response
        char response_message[BUFFER_SIZE];
        snprintf(response_message, sizeof(response_message), 
                 "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);

        // Write the response to the file stream
        fprintf(response, "%s", response_message);
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("response.txt", "w");
    if (!response) {
        perror("Failed to open response file");
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}