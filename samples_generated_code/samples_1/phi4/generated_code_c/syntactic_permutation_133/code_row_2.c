#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HTTP_STATUS_OK "200 OK"
#define REQUEST_METHOD_GET "GET"

typedef struct {
    const char *method;
    const char *path;
} request_t;

typedef struct {
    int status_code;
    const char *status_message;
    const char *body;
} response_t;

response_t handle_request(request_t req) {
    if (strcmp(req.method, REQUEST_METHOD_GET) == 0 && strcmp(req.path, "/") == 0) {
        return (response_t){200, HTTP_STATUS_OK, "Hello, World!"};
    }
    return (response_t){404, "404 Not Found", "Not found"};
}

void run_server() {
    char input[1024];
    printf("Enter request method and path (e.g., GET /): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    char *method = strtok(input, " ");
    char *path = strtok(NULL, " ");

    if (method && path) {
        request_t req = {method, path};
        response_t res = handle_request(req);

        printf("Status: %d %s\n", res.status_code, res.status_message);
        printf("Body:\n%s\n", res.body);
    } else {
        fprintf(stderr, "Invalid input.\n");
    }
}

int main() {
    run_server();
    return 0;
}