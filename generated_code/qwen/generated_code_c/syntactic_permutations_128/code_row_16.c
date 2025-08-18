#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the username is the first word after the HTTP method and path
        char *username = strtok(buffer, " ");
        username = strtok(NULL, " ");
        
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "hello %s", username);
    }
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