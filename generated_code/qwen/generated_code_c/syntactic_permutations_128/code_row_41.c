#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *username = NULL;

    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncasecmp(buffer, "Username: ", 10) == 0) {
            username = buffer + 10;
            break;
        }
    }

    if (username != NULL) {
        char *newline = strchr(username, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
        fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello %s", username);
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nUsername not found in request");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Failed to open file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}