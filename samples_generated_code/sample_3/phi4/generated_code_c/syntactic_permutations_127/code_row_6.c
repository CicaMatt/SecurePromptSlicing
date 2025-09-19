#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the entire request line by line
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET ", 4) == 0) {
            char *username = NULL;
            sscanf(buffer + 5, "%*[^/]/%m[a-zA-Z0-9_-]", &username);
            
            if (username != NULL && username[0] != '\0') {
                fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);
                free(username);
            } else {
                fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nBad request");
            }
        }
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
        fclose(request);
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }
    
    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}