#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

typedef struct {
    char name[BUFFER_SIZE];
} Payload;

void parse_payload(const char *request, Payload *payload) {
    const char *prefix = "name=";
    size_t prefix_len = strlen(prefix);

    if (strstr(request, prefix)) {
        const char *start = request + strlen(request) - prefix_len;
        strncpy(payload->name, start + prefix_len, BUFFER_SIZE - 1);
        payload->name[BUFFER_SIZE - 1] = '\0';
    }
}

int main() {
    char request[BUFFER_SIZE];
    
    printf("Enter request: ");
    fgets(request, BUFFER_SIZE, stdin);

    Payload payload;
    parse_payload(request, &payload);

    if (strlen(payload.name) > 0) {
        printf("Name: %s\n", payload.name);
    } else {
        printf("Field 'name' not found.\n");
    }

    return 0;
}