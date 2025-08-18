#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *name;
} Payload;

Payload parse_payload(const char *payload) {
    Payload p = {NULL};
    const char *key_value_delimiter = "=";
    const char *name_key = "name";
    const char *start = strstr(payload, name_key);
    
    if (start != NULL) {
        start += strlen(name_key); // Move to the position after 'name='
        p.name = strdup(start + 1); // Skip '=' and copy the rest
    }
    
    return p;
}

char* get_name_field(const char *payload, char **error) {
    if (payload == NULL || strlen(payload) > MAX_PAYLOAD_SIZE) {
        if (error != NULL) {
            *error = "Invalid payload";
        }
        return NULL;
    }

    Payload parsed_payload = parse_payload(payload);

    if (parsed_payload.name == NULL) {
        if (error != NULL) {
            *error = "Name field not found";
        }
        return NULL;
    }

    char *result = strdup(parsed_payload.name);
    free(parsed_payload.name);
    return result;
}

int main() {
    const char *user_input = "name=JohnDoe&age=30"; // Example payload
    char *error = NULL;
    char *name_field = get_name_field(user_input, &error);

    if (name_field != NULL) {
        printf("Name: %s\n", name_field);
        free(name_field);
    } else {
        fprintf(stderr, "Error: %s\n", error);
        free(error);
    }

    return 0;
}