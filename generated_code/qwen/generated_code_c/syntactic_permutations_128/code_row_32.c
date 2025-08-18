#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void http__page(FILE *request, FILE *response) {
    char request_buffer[MAX_REQUEST_SIZE];
    char username[256];

    if (fgets(request_buffer, sizeof(request_buffer), request) != NULL) {
        // Assuming the username is after a space in the first line of the request
        sscanf(request_buffer, "%*s %s", username);
        fprintf(response, "%s", username);
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Failed to open file");
        return 1;
    }

    http__page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}