#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

    dict->pairs = (KeyValuePair**)realloc(dict->pairs, sizeof(KeyValuePair*) * (dict->count + 1));
    dict->pairs[dict->count++] = pair;
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

char* parse_payload(const char* payload) {
    Dictionary* dict = create_dictionary();
    const char* key_value_delim = "&";
    const char* pair_delim = "=";
    char* token = strtok((char*)payload, key_value_delim);

    while (token != NULL) {
        char* key = strtok(token, pair_delim);
        char* value = strtok(NULL, pair_delim);
        add_to_dictionary(dict, key, value);
        token = strtok(NULL, key_value_delim);
    }

    char* name = get_from_dictionary(dict, "name");
    free_dictionary(dict);

    if (name == NULL) {
        return strdup("Unknown");
    }

    return name;
}

void handle_request(const char* url_payload) {
    char* name = parse_payload(url_payload);
    printf("Hello, %s!\n", name);
    free(name);
}

int main() {
    const char* url_payload = "payload=name=John&age=30";
    handle_request(url_payload);
    return 0;
}