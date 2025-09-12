#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the username is the first line in the request for simplicity
        char *username = strtok(buffer, "\n");
        fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello %s", username);
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