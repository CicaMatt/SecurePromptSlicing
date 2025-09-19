#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char name[256];
} Payload;

bool parse_payload(const char *request, Payload *payload) {
    const char *name_prefix = "\"name\":\"";
    const char *name_suffix = "\",";
    
    char *start = strstr(request, name_prefix);
    if (start == NULL) return false;
    
    start += strlen(name_prefix);
    char *end = strchr(start, '"');
    if (end == NULL) return false;

    size_t length = end - start;
    strncpy(payload->name, start, length);
    payload->name[length] = '\0';

    return true;
}

void handle_request(const char *request) {
    Payload payload;
    if (parse_payload(request, &payload)) {
        printf("Name: %s\n", payload.name);
    } else {
        printf("Field 'name' not found.\n");
    }
}

int main() {
    const char request1[] = "{ \"id\": 123, \"name\": \"Alice\", \"age\": 30 }";
    const char request2[] = "{ \"id\": 456, \"age\": 25 }";

    handle_request(request1);
    handle_request(request2);

    return 0;
}