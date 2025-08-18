#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *name;
} Payload;

int parse_payload(const char *input, Payload *payload) {
    const char *key_name = "name=";
    char *start, *end;
    
    start = strstr(input, key_name);
    if (start == NULL) {
        return 0; // Field 'name' not found
    }
    
    start += strlen(key_name); // Move to the beginning of the value
    end = strchr(start, '&');
    
    if (end != NULL) {
        size_t length = end - start;
        payload->name = malloc(length + 1);
        strncpy(payload->name, start, length);
        payload->name[length] = '\0';
    } else {
        // No '&' found, take the rest of the string
        payload->name = strdup(start);
    }
    
    return 1; // Field 'name' found
}

int main() {
    char input[MAX_PAYLOAD_SIZE];
    Payload payload;
    
    printf("Enter payload: ");
    if (fgets(input, MAX_PAYLOAD_SIZE, stdin) != NULL) {
        if (parse_payload(input, &payload)) {
            printf("Name: %s\n", payload.name);
            free(payload.name);
        } else {
            printf("Field 'name' not found.\n");
        }
    }
    
    return 0;
}