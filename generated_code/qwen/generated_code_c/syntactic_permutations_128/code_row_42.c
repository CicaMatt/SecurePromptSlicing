#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *prefix = "username=";
    char username[1024];

    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, prefix, strlen(prefix)) == 0) {
            strncpy(username, buffer + strlen(prefix), sizeof(username));
            // Remove newline character from the end of the username
            username[strcspn(username, "\r\n")] = '\0';
            break;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Failed to open files");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}