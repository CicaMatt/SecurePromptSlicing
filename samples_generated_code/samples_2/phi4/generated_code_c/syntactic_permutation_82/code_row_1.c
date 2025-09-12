#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char key[MAX_PAYLOAD_SIZE];
    char value[MAX_PAYLOAD_SIZE];
} KeyValuePair;

typedef struct {
    int size;
    KeyValuePair *pairs;
} Dictionary;

Dictionary create_dictionary() {
    return (Dictionary){0, NULL};
}

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    dict->size++;
    dict->pairs = realloc(dict->pairs, dict->size * sizeof(KeyValuePair));
    strncpy(dict->pairs[dict->size - 1].key, key, MAX_PAYLOAD_SIZE);
    strncpy(dict->pairs[dict->size - 1].value, value, MAX_PAYLOAD_SIZE);
}

char* get_value_from_dictionary(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            return dict->pairs[i].value;
        }
    }
    return NULL;
}

void handle_request(const char *payload) {
    Dictionary dict = create_dictionary();
    
    // Simulate parsing the payload into dictionary entries
    const char *delimiter = "&";
    char *token = strtok((char *)payload, delimiter);
    while (token != NULL) {
        char *equal_sign = strchr(token, '=');
        if (equal_sign != NULL) {
            *equal_sign = '\0';
            add_to_dictionary(&dict, token, equal_sign + 1);
        }
        token = strtok(NULL, delimiter);
    }

    const char *name_value = get_value_from_dictionary(&dict, "name");
    if (name_value != NULL) {
        printf("Name: %s\n", name_value);
    } else {
        printf("Name not found in payload.\n");
    }
    
    free(dict.pairs);
}

int main() {
    const char *payload = "name=JohnDoe&age=30";
    handle_request(payload);

    return 0;
}