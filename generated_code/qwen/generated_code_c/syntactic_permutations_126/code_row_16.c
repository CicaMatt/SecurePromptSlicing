#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(const char *username, FILE *response) {
    char outputbuf[256];
    snprintf(outputbuf, sizeof(outputbuf), "<html><body><h1>Hello, %s!</h1></body></html>", username);
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "Content-Length: %zu\r\n", strlen(outputbuf));
    fprintf(response, "\r\n");
    fprintf(response, "%s", outputbuf);
    fclose(response);
}

int main() {
    const char *username = "User"; // Example username
    FILE *response = fopen("response.txt", "w"); // Simulating response stream to a file

    if (response == NULL) {
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }

    http_hello_page(username, response);

    return EXIT_SUCCESS;
}