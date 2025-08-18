#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the username is sent as the first line in the request
        char *username = strtok(buffer, "\n");
        fprintf(response, "Hello %s", username);
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Failed to open files");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}