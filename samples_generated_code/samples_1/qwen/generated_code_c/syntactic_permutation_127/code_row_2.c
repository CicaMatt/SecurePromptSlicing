#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void http_hello_page(FILE *request, FILE *response) {
    char line[MAX_LINE_LENGTH];
    char username[MAX_LINE_LENGTH] = "";
    int found_username = 0;

    while (fgets(line, sizeof(line), request) != NULL) {
        if (sscanf(line, "username=%s", username) == 1) {
            found_username = 1;
            break;
        }
    }

    if (found_username) {
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s", username);
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Username not found in request.");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;

    if (request == NULL) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    return EXIT_SUCCESS;
}