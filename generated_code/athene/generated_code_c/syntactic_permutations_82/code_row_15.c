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
    KeyValuePair** new_pairs = (KeyValuePair**)realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair*));
    if (!new_pairs) return;

    dict->pairs = new_pairs;
    dict->pairs[dict->count] = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    dict->pairs[dict->count]->key = strdup(key);
    dict->pairs[dict->count]->value = strdup(value);

    dict->count++;
}

char* get_from_dictionary(Dictionary* dict, const char* key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary* dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
    free(dict);
}

char* handle_api_request(const char* payload) {
    Dictionary* dict = create_dictionary();
    const char* key;
    const char* value;

    // Simple parsing of the payload into a dictionary
    char* copy = strdup(payload);
    char* token = strtok(copy, "&");
    while (token != NULL) {
        key = strtok(token, "=");
        value = strtok(NULL, "=");
        if (key && value) {
            add_to_dictionary(dict, key, value);
        }
        token = strtok(NULL, "&");
    }

    char* name = get_from_dictionary(dict, "name");
    free(copy);
    free_dictionary(dict);

    return name;
}

int main() {
    const char* payload = "name=John&age=30";
    char* name = handle_api_request(payload);
    if (name) {
        printf("Name: %s\n", name);
    } else {
        printf("Name not found in payload.\n");
    }
    free(name); // Free the string returned by get_from_dictionary
    return 0;
}