#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the username is sent in plain text and is the first line
        strncpy(username, buffer, sizeof(username));
        username[strcspn(username, "\n")] = 0; // Remove newline character

        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "Connection: close\r\n\r\n");
        fprintf(response, "Hello %s", username);
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Error opening files");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}