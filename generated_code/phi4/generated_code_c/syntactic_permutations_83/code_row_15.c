#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char name[MAX_PAYLOAD_SIZE];
} Payload;

Payload parse_payload(const char* input) {
    Payload payload = { .name[0] = '\0' };
    
    const char *start = strstr(input, "name=\"");
    if (start) {
        start += strlen("name=\""); // Move past 'name="'
        
        const char *end = strchr(start, '"');
        if (end && end != start) {
            size_t name_length = end - start;
            strncpy(payload.name, start, name_length);
            payload.name[name_length] = '\0';
        }
    }

    return payload;
}

int main() {
    printf("Enter payload: ");
    char input[MAX_PAYLOAD_SIZE];
    if (fgets(input, MAX_PAYLOAD_SIZE, stdin)) {
        Payload payload = parse_payload(input);
        
        if (payload.name[0] != '\0') {
            printf("Name found: %s\n", payload.name);
        } else {
            printf("Name not found.\n");
        }
    }

    return 0;
}