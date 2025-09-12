#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];
    int username_length = 0;

    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "Username:", 9) == 0) {
            sscanf(buffer + 9, "%s", username);
            username_length = strlen(username);
            break;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "Content-Length: %zu\r\n", 6 + username_length);
    fprintf(response, "\r\n");
    fprintf(response, "Hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}