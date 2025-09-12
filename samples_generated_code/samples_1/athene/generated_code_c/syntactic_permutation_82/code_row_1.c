#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair** pairs;
    int count;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->pairs = NULL;
    dict->count = 0;
    return dict;
}

void add_to_dictionary(Dictionary* dict, const char* key, const char* value) {
    KeyValuePair* pair = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);

    dict->pairs = (KeyValuePair**)realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair*));
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

char* parse_payload(const char* payload, const char* param) {
    Dictionary* dict = create_dictionary();
    char* payload_copy = strdup(payload);
    char* token = strtok(payload_copy, "&");
    while (token != NULL) {
        char* key = strtok(token, "=");
        char* value = strtok(NULL, "=");
        if (key && value) {
            add_to_dictionary(dict, key, value);
        }
        token = strtok(NULL, "&");
    }

    char* result = get_from_dictionary(dict, param);
    free(payload_copy);
    free_dictionary(dict);
    return result;
}

int main() {
    const char* payload = "name=John&age=30";
    const char* name = parse_payload(payload, "name");
    if (name) {
        printf("%s\n", name);
    } else {
        printf("Parameter not found\n");
    }
    return 0;
}