#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    int count;
    KeyValuePair **pairs;
} Dictionary;

Dictionary *create_dictionary() {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->pairs = NULL;
    return dict;
}

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    KeyValuePair *pair = (KeyValuePair *)malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);
    dict->pairs = (KeyValuePair **)realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair *));
    dict->pairs[dict->count++] = pair;
}

char *get_from_dictionary(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
    free(dict);
}

char *parse_payload(const char *payload) {
    Dictionary *dict = create_dictionary();
    const char *token;
    token = strtok((char *)payload, "&");
    while (token != NULL) {
        char *key, *value;
        key = strtok((char *)token, "=");
        value = strtok(NULL, "=");
        add_to_dictionary(dict, key, value);
        token = strtok(NULL, "&");
    }
    char *name = get_from_dictionary(dict, "name");
    free_dictionary(dict);
    return name ? strdup(name) : NULL;
}

int main() {
    const char *url_payload = "payload=name=JohnDoe&age=30";
    const char *query = strstr(url_payload, "=") + 1; // Skip the first key
    char *name = parse_payload(query);
    if (name != NULL) {
        printf("Name: %s\n", name);
        free(name);
    } else {
        printf("Name not found.\n");
    }
    return 0;
}