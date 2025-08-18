#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 2048

void http_hello_page(FILE *request, FILE *response) {
    char username[MAX_REQUEST_SIZE] = "";
    fread(username, sizeof(char), MAX_REQUEST_SIZE - 1, request);
    username[strcspn(username, "\r\n")] = 0; // Remove trailing newline or carriage return

    char outputbuf[MAX_RESPONSE_SIZE];
    snprintf(outputbuf, MAX_RESPONSE_SIZE, "Hello, %s!", username);

    fwrite(outputbuf, sizeof(char), strlen(outputbuf), response);
    fclose(response);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    return 0;
}