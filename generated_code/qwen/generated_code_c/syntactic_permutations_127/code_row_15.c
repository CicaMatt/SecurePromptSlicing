#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[MAX_REQUEST_SIZE];
    const char *username = NULL;

    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the username is sent as a single line in the request
        username = strtok(buffer, "\n");
    }

    if (username != NULL) {
        fprintf(response, "Hello %s", username);
    } else {
        fprintf(response, "Hello Guest");
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