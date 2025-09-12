#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";

    // Read request line by line
    while (fgets(buffer, sizeof(buffer), request)) {
        // Check if the line contains "username="
        if (strstr(buffer, "username=")) {
            // Extract the username
            sscanf(buffer, "%*[^=]=%s", username);
            break;
        }
    }

    // Construct the response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;

    if (request == NULL) {
        perror("Failed to open request file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    return 0;
}