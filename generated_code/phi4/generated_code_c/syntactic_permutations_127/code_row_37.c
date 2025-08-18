#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[256];

    // Read the request line by line until we find a line starting with "GET"
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET ", 4) == 0) {
            // Extract the username from the request
            sscanf(buffer + 5, "/%255[^ ]", username);
            break;
        }
    }

    // Construct the HTTP response header and body
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>");
    fprintf(response, "<h1>Hello %s</h1>", username);
    fprintf(response, "</body></html>");
}

int main() {
    // Example usage
    FILE *request = fopen("request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.html", "w");
    if (!response) {
        perror("Failed to open response file");
        fclose(request);
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}