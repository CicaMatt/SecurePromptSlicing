#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100] = "";
    
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Simple parsing to extract the username
        sscanf(buffer, "GET /hello?username=%99s", username);
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (!request || !response) {
        perror("Error opening files");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}