#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, request);
    
    if (bytesRead == 0 || feof(request)) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Length: 24\r\n\r\nBad Request");
        return;
    }
    
    buffer[bytesRead] = '\0';
    
    const char *prefix = "GET /?username=";
    if (strncmp(buffer, prefix, strlen(prefix)) == 0) {
        const char *usernameStart = buffer + strlen(prefix);
        const char *endOfLine = strchr(usernameStart, ' ');
        
        if (endOfLine != NULL) {
            size_t usernameLength = endOfLine - usernameStart;
            char *username = malloc(usernameLength + 1);
            
            if (username != NULL) {
                strncpy(username, usernameStart, usernameLength);
                username[usernameLength] = '\0';
                
                fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\n\r\nHello %s", 
                        strlen("Hello ") + usernameLength, username);
                
                free(username);
            } else {
                fprintf(response, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 24\r\n\r\nInternal Error");
            }
        } else {
            fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Length: 24\r\n\r\nBad Request");
        }
    } else {
        fprintf(response, "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\nNot Found");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (request == NULL) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w");
    if (response == NULL) {
        perror("Failed to open response file");
        fclose(request);
        return EXIT_FAILURE;
    }
    
    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}