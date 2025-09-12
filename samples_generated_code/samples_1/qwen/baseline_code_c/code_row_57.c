#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the username is sent as the first line in the request
        sscanf(buffer, "%s", username);

        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s\n", username);
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Failed to open file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}