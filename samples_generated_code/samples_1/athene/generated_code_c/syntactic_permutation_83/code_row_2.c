#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void handle_request(const char *request, char *response) {
    const char *field_name = "name=";
    size_t field_len = strlen(field_name);
    const char *start = strstr(request, field_name);

    if (start == NULL) {
        strcpy(response, "");
    } else {
        start += field_len;
        const char *end = strchr(start, '&');
        if (end == NULL) {
            strncpy(response, start, MAX_REQUEST_SIZE - 1);
            response[MAX_REQUEST_SIZE - 1] = '\0';
        } else {
            size_t len = end - start;
            strncpy(response, start, len);
            response[len] = '\0';
        }
    }
}

int main() {
    char request[MAX_REQUEST_SIZE];
    char response[MAX_REQUEST_SIZE];

    // Simulate a user request
    fgets(request, MAX_REQUEST_SIZE, stdin);

    handle_request(request, response);

    printf("Content-Type: text/plain\r\n\r\n");
    printf("%s", response);

    return 0;
}