#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *name;
} Request;

int parse_payload(const char *payload, size_t length, Request *request) {
    char key[MAX_PAYLOAD_SIZE];
    char value[MAX_PAYLOAD_SIZE];

    const char *start = payload;
    while (*start && start < payload + length - 1) {
        if (sscanf(start, "%[^=]=%[^\n]", key, value) == 2) {
            if (strcmp(key, "name") == 0) {
                request->name = malloc(strlen(value) + 1);
                strcpy(request->name, value);
                return 0;
            }
        }
        start = strchr(start, '\n');
        if (!start)
            break;
        ++start;
    }

    return -1; // Error: name not found
}

const char* handle_request(const char *payload) {
    Request request = {NULL};
    int result = parse_payload(payload, strlen(payload), &request);

    const char *response;
    if (result == 0 && request.name != NULL) {
        response = request.name;
    } else {
        response = "Name not found";
    }

    free(request.name);
    return response;
}

void simulate_web_server() {
    // Simulated payload received from the /api route
    const char *payload = "name=JohnDoe\nother_param=value\n";

    const char *response = handle_request(payload);

    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s", response);
}

int main() {
    simulate_web_server();
    return 0;
}