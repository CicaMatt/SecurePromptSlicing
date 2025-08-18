#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100] = "";
    
    while (fgets(buffer, sizeof(buffer), request) != NULL) {
        if (strncmp(buffer, "username=", 9) == 0) {
            strncpy(username, buffer + 9, sizeof(username) - 1);
            // Remove newline character if present
            username[strcspn(username, "\r\n")] = '\0';
            break;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body><h1>Hello %s</h1></body></html>", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Error opening file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}