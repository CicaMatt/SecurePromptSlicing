#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Move to the start of the line containing "username="
    fseek(request, 0, SEEK_SET);
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "username=", 9) == 0) {
            break;
        }
    }

    char *username_start = buffer + 9;
    char username[BUFFER_SIZE];
    
    // Extract the username
    sscanf(username_start, "%[^&\r\n]", username);
    
    // Construct and send the response
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    fprintf(response, "Hello %s", username);
}

int main() {
    // Example usage
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