#include <stdio.h>
#include <string.h>

#define REQUEST_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[REQUEST_SIZE];
    char username[REQUEST_SIZE];
    fgets(buffer, sizeof(buffer), request);
    sscanf(buffer, "GET /hello?username=%s", username);

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (!request || !response) {
        perror("Failed to open file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}