#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    char username[256] = {0};
    
    // Read the request line by line to find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "GET /?username=") == buffer) {
            sscanf(buffer, "GET /?username=%255s", username);
            break;
        }
    }

    // Construct and send the response
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