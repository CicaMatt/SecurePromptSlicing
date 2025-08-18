#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    fgets(buffer, sizeof(buffer), request);

    // Extract username from the request (assuming a simple GET /?username=... format)
    const char *prefix = "GET /?username=";
    if (strncmp(buffer, prefix, strlen(prefix)) == 0) {
        const char *username_start = buffer + strlen(prefix);
        char *username_end = strchr(username_start, ' ');
        if (username_end != NULL) {
            size_t username_length = username_end - username_start;
            char username[256];
            
            // Copy the username safely
            strncpy(username, username_start, username_length);
            username[username_length] = '\0';

            // Construct response
            fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
            fprintf(response, "Hello %s", username);
        } else {
            fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request format.");
        }
    } else {
        fprintf(response, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nPage not found.");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (request == NULL) {
        perror("Error opening request file");
        return 1;
    }

    FILE *response = fopen("response.txt", "w");
    if (response == NULL) {
        fclose(request);
        perror("Error opening response file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);
    
    return 0;
}