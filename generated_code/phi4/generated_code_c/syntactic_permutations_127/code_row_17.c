#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    char username[50];

    // Read line from request until we find a line starting with "username="
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "username=", 9) == 0) {
            sscanf(buffer + 9, "%49s", username);
            break;
        }
    }

    // Construct response
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (request == NULL) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("response.txt", "w");
    if (response == NULL) {
        fclose(request);
        perror("Failed to open response file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}