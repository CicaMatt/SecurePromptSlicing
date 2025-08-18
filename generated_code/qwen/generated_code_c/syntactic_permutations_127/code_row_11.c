#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    if (fgets(buffer, sizeof(buffer), request)) {
        // Assuming the first line contains the username
        sscanf(buffer, "%s", username);

        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/html\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "<html><body>");
        fprintf(response, "<h1>Hello %s</h1>", username);
        fprintf(response, "</body></html>\r\n");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}