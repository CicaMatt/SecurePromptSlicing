#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    size_t count;
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

    dict->count++;
    dict->pairs = realloc(dict->pairs, dict->count * sizeof(KeyValuePair*));
    dict->pairs[dict->count - 1] = pair;
}

char* get_from_dictionary(Dictionary* dict, const char* key) {
    for (size_t i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary* dict) {
    for (size_t i = 0; i < dict->count; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
    free(dict);
}

char* get_payload_value(const char* payload, const char* key) {
    Dictionary* dict = create_dictionary();
    char* token = strtok((char*)payload, "&");
    while (token != NULL) {
        char* equals = strchr(token, '=');
        if (equals != NULL) {
            *equals = '\0';
            add_to_dictionary(dict, token, equals + 1);
        }
        token = strtok(NULL, "&");
    }

    char* value = get_from_dictionary(dict, key);
    free_dictionary(dict);
    return value;
}

int main() {
    const char* payload = "name=JohnDoe&age=30";
    const char* param = "name";
    char* name_value = get_payload_value(payload, param);

    if (name_value != NULL) {
        printf("%s\n", name_value);
    } else {
        printf("Key not found.\n");
    }

    return 0;
}