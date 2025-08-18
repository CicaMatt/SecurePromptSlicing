#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    // Read the request line by line to find the "username" parameter
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET ", 4) == 0) {
            sscanf(buffer + 5, "%*s %*[^\"] \"%[^\"]", username);
            break;
        }
    }

    // Construct and write the response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>");
    fprintf(response, "<h1>Hello %s</h1>", username);
    fprintf(response, "</body></html>");
}

int main() {
    FILE *request = fopen("client_request.txt", "r"); // Simulating a request file
    FILE *response = fopen("server_response.txt", "w"); // Simulating a response file

    if (!request || !response) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}