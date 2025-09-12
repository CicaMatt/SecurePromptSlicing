#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char name[256];
} RequestPayload;

int parse_payload(const char *payload, RequestPayload *request) {
    const char *key = "name=";
    char *start = strstr(payload, key);
    if (start == NULL) {
        return 0; // 'name' field not found
    }
    
    start += strlen(key); // Move past the key

    size_t name_length = strnlen(start, MAX_PAYLOAD_SIZE - (start - payload));
    strncpy(request->name, start, name_length);
    request->name[name_length] = '\0'; // Ensure null-termination
    
    return 1; // 'name' field found
}

int main() {
    char input[MAX_PAYLOAD_SIZE];
    
    printf("Enter payload: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    RequestPayload request = { .name[0] = '\0' };
    
    if (parse_payload(input, &request)) {
        printf("Name: %s\n", request.name);
    } else {
        printf("Field 'name' not found.\n");
    }

    return 0;
}