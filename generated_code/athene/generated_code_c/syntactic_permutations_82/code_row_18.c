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
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->pairs = NULL;
    return dict;
}

void add_to_dictionary(Dictionary* dict, const char* key, const char* value) {
    KeyValuePair* pair = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);
    dict->pairs = (KeyValuePair**)realloc(dict->pairs, sizeof(KeyValuePair*) * (dict->count + 1));
    dict->pairs[dict->count++] = pair;
}

char* get_from_dictionary(Dictionary* dict, const char* key) {
    for (int i = 0; i < dict->count; ++i) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary* dict) {
    for (int i = 0; i < dict->count; ++i) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
    free(dict);
}

char* get_payload_value(const char* payload, const char* key) {
    Dictionary* dict = create_dictionary();
    char* token;
    char* dup = strdup(payload);

    // Parse the payload into a dictionary
    token = strtok(dup, "&");
    while (token != NULL) {
        char* eq = strchr(token, '=');
        if (eq != NULL) {
            *eq = '\0';
            add_to_dictionary(dict, token, eq + 1);
        }
        token = strtok(NULL, "&");
    }

    // Get the value for the key
    char* value = get_from_dictionary(dict, key);

    free(dup);
    free_dictionary(dict);
    return value;
}

// Simulate a web request handler
void handle_request(const char* payload) {
    char* name_value = get_payload_value(payload, "name");
    if (name_value != NULL) {
        printf("Name: %s\n", name_value);
    } else {
        printf("Name not found in payload.\n");
    }
}

int main() {
    const char* payload = "name=John Doe&age=30";
    handle_request(payload);
    return 0;
}