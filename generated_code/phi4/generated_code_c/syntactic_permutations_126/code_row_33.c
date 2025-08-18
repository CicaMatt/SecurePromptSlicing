#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUEST_BODY_SIZE 1024

void http_hello_page(const char *request_body, size_t request_body_length, char **outputbuf, size_t *outputbuf_size) {
    char username[REQUEST_BODY_SIZE];
    strncpy(username, request_body, request_body_length);
    username[request_body_length] = '\0'; // Ensure null termination

    size_t response_size = snprintf(NULL, 0,
        "<html><head><title>Hello Page</title></head>"
        "<body><h1>Hello, %s!</h1></body></html>", username) + 1;

    *outputbuf = (char *)malloc(response_size);
    if (*outputbuf == NULL) {
        perror("Failed to allocate memory for response");
        exit(EXIT_FAILURE);
    }

    snprintf(*outputbuf, response_size,
        "<html><head><title>Hello Page</title></head>"
        "<body><h1>Hello, %s!</h1></body></html>", username);

    *outputbuf_size = response_size;
}

int main() {
    const char *request_body = "JohnDoe";
    size_t request_body_length = strlen(request_body);
    
    char *response_body = NULL;
    size_t response_body_size = 0;

    http_hello_page(request_body, request_body_length, &response_body, &response_body_size);

    printf("Response Body:\n%s\n", response_body);

    free(response_body);
    return 0;
}