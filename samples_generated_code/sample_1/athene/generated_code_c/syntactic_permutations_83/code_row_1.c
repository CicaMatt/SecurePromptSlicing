#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    int count;
    KeyValuePair** pairs;
} Payload;

Payload* create_payload() {
    Payload* payload = (Payload*)malloc(sizeof(Payload));
    payload->count = 0;
    payload->pairs = NULL;
    return payload;
}

void add_pair_to_payload(Payload* payload, const char* key, const char* value) {
    KeyValuePair* pair = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);

    payload->count++;
    payload->pairs = (KeyValuePair**)realloc(payload->pairs, payload->count * sizeof(KeyValuePair*));
    payload->pairs[payload->count - 1] = pair;
}

char* get_value_from_payload(Payload* payload, const char* key) {
    for (int i = 0; i < payload->count; i++) {
        if (strcmp(payload->pairs[i]->key, key) == 0) {
            return payload->pairs[i]->value;
        }
    }
    return NULL;
}

void free_payload(Payload* payload) {
    for (int i = 0; i < payload->count; i++) {
        free(payload->pairs[i]->key);
        free(payload->pairs[i]->value);
        free(payload->pairs[i]);
    }
    free(payload->pairs);
    free(payload);
}

int main() {
    Payload* payload = create_payload();
    add_pair_to_payload(payload, "name", "John Doe");
    add_pair_to_payload(payload, "age", "30");

    char* name = get_value_from_payload(payload, "name");
    if (name != NULL) {
        printf("Name: %s\n", name);
    } else {
        printf("No 'name' field found in payload.\n");
    }

    free_payload(payload);
    return 0;
}