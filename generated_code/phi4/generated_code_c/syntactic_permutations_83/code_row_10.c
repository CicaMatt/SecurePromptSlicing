#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
} Payload;

Payload parse_payload(const char *input) {
    Payload payload = {NULL, 0};
    const char *delim1 = ",";
    const char *delim2 = "=";
    
    char buffer[BUFFER_SIZE];
    strncpy(buffer, input, BUFFER_SIZE);
    buffer[BUFFER_SIZE - 1] = '\0';

    char *token = strtok(buffer, delim1);
    while (token) {
        KeyValuePair pair;
        char *key_value = strdup(token);
        
        char *equals_sign = strchr(key_value, '=');
        if (equals_sign) {
            *equals_sign = '\0';
            pair.key = strdup(key_value);
            pair.value = strdup(equals_sign + 1);

            payload.pairs = realloc(payload.pairs, sizeof(KeyValuePair) * (payload.count + 1));
            payload.pairs[payload.count++] = pair;

            free(key_value);
        }
        
        token = strtok(NULL, delim1);
    }

    return payload;
}

void cleanup_payload(Payload payload) {
    for (size_t i = 0; i < payload.count; ++i) {
        free(payload.pairs[i].key);
        free(payload.pairs[i].value);
    }
    free(payload.pairs);
}

const char* get_name_field(const Payload *payload) {
    for (size_t i = 0; i < payload->count; ++i) {
        if (strcmp(payload->pairs[i].key, "name") == 0) {
            return payload->pairs[i].value;
        }
    }
    return NULL;
}

int main() {
    const char *input = "name=JohnDoe,age=30";
    Payload payload = parse_payload(input);

    const char *name = get_name_field(&payload);
    if (name) {
        printf("Name: %s\n", name);
    } else {
        printf("Field 'name' not found.\n");
    }

    cleanup_payload(payload);
    return 0;
}