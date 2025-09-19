#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char name[256];
} Payload;

Payload parse_payload(const char *request) {
    Payload payload;
    memset(&payload, 0, sizeof(Payload));

    // Check if 'name' field exists in the request
    const char *name_prefix = "name=";
    size_t prefix_len = strlen(name_prefix);
    const char *name_start = strstr(request, name_prefix);

    if (name_start) {
        name_start += prefix_len;
        const char *name_end = strchr(name_start, '&');
        if (!name_end) {
            name_end = request + strlen(request);
        }
        size_t name_length = name_end - name_start;

        if (name_length < sizeof(payload.name)) {
            strncpy(payload.name, name_start, name_length);
            payload.name[name_length] = '\0';
        }
    }

    return payload;
}

int main() {
    char request[MAX_PAYLOAD_SIZE];

    // Simulate a user input
    printf("Enter the request: ");
    if (fgets(request, sizeof(request), stdin) != NULL) {
        Payload payload = parse_payload(request);

        if (payload.name[0] != '\0') {
            printf("Name: %s\n", payload.name);
        } else {
            printf("Field 'name' not found.\n");
        }
    }

    return 0;
}