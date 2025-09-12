#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[50];

    while (fgets(buffer, sizeof(buffer), request)) {
        if (sscanf(buffer, "username=%49s", username) == 1) {
            break;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "Hello %s\n", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;

    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    return EXIT_SUCCESS;
}