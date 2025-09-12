#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the first line of the request contains the URL or path
        char *name_start = strchr(buffer, ' ');
        if (name_start != NULL) {
            name_start++; // Move past the space
            char *name_end = strchr(name_start, ' ');
            if (name_end != NULL) {
                *name_end = '\0'; // Null-terminate the name
                fprintf(response, "HTTP/1.1 200 OK\r\n");
                fprintf(response, "Content-Type: text/plain\r\n");
                fprintf(response, "\r\n");
                fprintf(response, "hello %s", name_start);
            }
        }
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