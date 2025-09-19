#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
    char name[MAX_LINE_LENGTH];
} Payload;

Payload parse_payload(const char *payload) {
    Payload p = {0};
    char *key, *value;
    const char *delimiter1 = "name=";
    const char *delimiter2 = "&";

    char *line = strdup(payload);
    key = strtok(line, delimiter1);
    
    if (key != NULL && strstr(line, delimiter1) != NULL) {
        value = strstr(line, delimiter1) + strlen(delimiter1);
        
        // Ensure that we stop at the next '&' or end of string
        char *end = strchr(value, '&');
        size_t length = end ? (size_t)(end - value) : strlen(value);

        strncpy(p.name, value, length < MAX_LINE_LENGTH ? length : MAX_LINE_LENGTH - 1);
    }

    free(line);
    return p;
}

void handle_request(const char *request) {
    if (strncmp(request, "POST / ", 7) == 0 || strncmp(request, "GET / ", 6) == 0) {
        const char *payload_start = strstr(request, "\r\n\r\n") + 4;
        Payload payload = parse_payload(payload_start);

        if (strlen(payload.name) > 0) {
            printf("Name: %s\n", payload.name);
        } else {
            printf("Field 'name' not found.\n");
        }
    } else {
        printf("Invalid request method.\n");
    }
}

int main() {
    const char *example_request = "POST / HTTP/1.1\r\n"
                                  "Host: localhost\r\n"
                                  "Content-Length: 15\r\n"
                                  "\r\n"
                                  "name=JohnDoe";

    handle_request(example_request);

    return 0;
}