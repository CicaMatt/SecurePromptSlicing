#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    int count;
    KeyValuePair **pairs;
} Payload;

Payload parse_payload(const char *payload_str) {
    Payload payload = {0, NULL};
    const char *data = payload_str;
    size_t len = strlen(payload_str);

    while (*data != '\0') {
        // Skip whitespace
        while (*data == ' ' || *data == ',' || *data == '{' || *data == '}') data++;

        if (*data == '\0') break;

        char key[BUFFER_SIZE] = {0};
        char value[BUFFER_SIZE] = {0};

        size_t i = 0;
        while (*data != '=' && i < BUFFER_SIZE - 1) {
            key[i++] = *data++;
        }
        key[i] = '\0';

        data++; // Skip the '='

        i = 0;
        if (*data == '"') { // Quoted value
            data++;
            while (*data != '"' && i < BUFFER_SIZE - 1) {
                value[i++] = *data++;
            }
        } else { // Unquoted value
            while (*data != ',' && *data != '}' && i < BUFFER_SIZE - 1) {
                value[i++] = *data++;
            }
        }
        value[i] = '\0';

        payload.count++;
        payload.pairs = realloc(payload.pairs, sizeof(KeyValuePair *) * payload.count);
        KeyValuePair *pair = malloc(sizeof(KeyValuePair));
        pair->key = strdup(key);
        pair->value = strdup(value);
        payload.pairs[payload.count - 1] = pair;

        while (*data != '\0' && (*data == ' ' || *data == ',' || *data == '}')) data++;
    }

    return payload;
}

void free_payload(Payload payload) {
    for (int i = 0; i < payload.count; i++) {
        free(payload.pairs[i]->key);
        free(payload.pairs[i]->value);
        free(payload.pairs[i]);
    }
    free(payload.pairs);
}

const char *get_name(const Payload payload) {
    for (int i = 0; i < payload.count; i++) {
        if (strcmp(payload.pairs[i]->key, "name") == 0) {
            return payload.pairs[i]->value;
        }
    }
    return NULL;
}

int main() {
    const char *input_payload = "{\"name\":\"John Doe\", \"age\":30}";
    Payload payload = parse_payload(input_payload);

    const char *name = get_name(payload);
    if (name) {
        printf("Name: %s\n", name);
    } else {
        printf("Name field not found.\n");
    }

    free_payload(payload);
    return 0;
}