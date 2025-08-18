#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 5000

typedef struct {
    char *payload;
} Request;

int starts_with(const char *pre, const char *str) {
    size_t len_pre = strlen(pre),
           len_str = strlen(str);
    return len_str < len_pre ? 0 : strncmp(pre, str, len_pre) == 0;
}

const char* parse_payload(Request request) {
    if (starts_with(request.payload, "type: Create")) {
        return "Error: Type is 'Create'";
    }
    return NULL;
}

Request parse_request(const char *raw_request) {
    Request req = { .payload = NULL };
    char *line = strtok(strdup(raw_request), "\r\n");
    
    while (line != NULL) {
        if (starts_with(line, "Payload: ")) {
            req.payload = strdup(&line[9]);
            break;
        }
        line = strtok(NULL, "\r\n");
    }

    return req;
}

const char* handle_request(const char *raw_request) {
    Request request = parse_request(raw_request);
    
    if (request.payload == NULL) {
        return "Error: Payload parameter is missing";
    }

    const char *error_message = parse_payload(request);
    free((void*)request.payload);

    return error_message ? error_message : "Request processed successfully";
}

int main() {
    printf("Listening on port %d...\n", PORT);
    
    char raw_request[] =
        "GET / HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "Payload: type: Create\r\n"
        "\r\n";

    const char *response = handle_request(raw_request);

    printf("Response: %s\n", response);

    return 0;
}