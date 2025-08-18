#include <stdio.h>
#include <string.h>

#define RESPONSE_BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char outputbuf[RESPONSE_BUFFER_SIZE];

    // Constructing the response body (HTML page)
    const char *htmlPage = 
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>Hello Page</title>\n"
        "</head>\n"
        "<body>\n"
        "    <h1>Hello, World!</h1>\n"
        "    <p>Welcome to the Hello Page.</p>\n"
        "</body>\n"
        "</html>";

    // Copying HTML page into output buffer
    strncpy(outputbuf, htmlPage, sizeof(outputbuf) - 1);
    outputbuf[sizeof(outputbuf) - 1] = '\0';

    // Writing the response body to the response stream
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fputs(outputbuf, response);

    // Flushing the output to ensure it's written
    fflush(response);
}

int main() {
    FILE *request = fopen("request.txt", "r");  // Simulating request input from a file
    if (request == NULL) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("response.txt", "w");  // Simulating response output to a file
    if (response == NULL) {
        perror("Failed to open response file");
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(response);
    fclose(request);

    return 0;
}