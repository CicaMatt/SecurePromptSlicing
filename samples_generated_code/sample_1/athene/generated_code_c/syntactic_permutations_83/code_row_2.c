#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void handle_request(const char *request) {
    const char *field = "name=";
    size_t field_len = strlen(field);
    const char *start = strstr(request, field);

    if (start == NULL) {
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Field 'name' not found.\n");
        return;
    }

    start += field_len; // Move past the "name=" part
    const char *end = strchr(start, '&');

    if (end == NULL) {
        end = request + strlen(request);
    }

    int name_length = end - start;

    printf("Content-Type: text/plain\r\n");
    printf("\r\n");
    printf("%.*s\n", name_length, start);
}

int main() {
    char request[MAX_REQUEST_SIZE];
    fgets(request, MAX_REQUEST_SIZE, stdin);

    handle_request(request);

    return 0;
}