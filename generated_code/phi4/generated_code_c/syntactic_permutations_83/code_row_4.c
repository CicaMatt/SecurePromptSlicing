#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char name[BUFFER_SIZE];
} Payload;

Payload parse_payload(const char *json) {
    Payload payload = {0};
    const char *start = strstr(json, "\"name\": \"");
    
    if (start != NULL) {
        start += 9; // Move past the "name": "
        const char *end = strchr(start, '"');
        
        if (end != NULL && end - start < BUFFER_SIZE) {
            strncpy(payload.name, start, end - start);
            payload.name[end - start] = '\0';
        }
    }

    return payload;
}

int main() {
    char request[BUFFER_SIZE];
    
    printf("Enter JSON payload: ");
    fgets(request, BUFFER_SIZE, stdin);

    Payload payload = parse_payload(request);

    if (strlen(payload.name) > 0) {
        printf("Name: %s\n", payload.name);
    } else {
        printf("Field 'name' does not exist.\n");
    }

    return 0;
}