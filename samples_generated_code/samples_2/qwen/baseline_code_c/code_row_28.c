#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    
    // Read the request line by line
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "username=") != NULL) {
            sscanf(buffer, "%*[^=]=%255s", username);
            break;
        }
    }

    // Construct and send response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s\r\n", username);
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