#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[MAX_REQUEST_SIZE];
    char username[64];

    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the username is sent as a query parameter in the format: /?username=[username]
        char *query = strchr(buffer, '?');
        if (query != NULL) {
            char *username_start = strstr(query, "username=");
            if (username_start != NULL) {
                username_start += strlen("username=");
                sscanf(username_start, "%63s", username);

                fprintf(response, "HTTP/1.1 200 OK\r\n");
                fprintf(response, "Content-Type: text/plain\r\n");
                fprintf(response, "\r\n");
                fprintf(response, "hello %s", username);
            }
        }
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