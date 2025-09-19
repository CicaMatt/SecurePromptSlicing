#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define MAX_PAYLOAD_LENGTH 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair **pairs;
    int size;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->size = 0;
    dict->pairs = NULL;
    return dict;
}

void add_to_dict(Dictionary *dict, char *key, char *value) {
    KeyValuePair *pair = malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);

    dict->size++;
    dict->pairs = realloc(dict->pairs, sizeof(KeyValuePair*) * dict->size);
    dict->pairs[dict->size - 1] = pair;
}

char* get_from_dict(Dictionary *dict, char *key) {
    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
    free(dict);
}

char* get_payload_from_url(char *url) {
    char *query = strchr(url, '?');
    if (query != NULL) {
        query++;
        return strdup(query);
    }
    return NULL;
}

Dictionary* parse_payload_to_dict(char *payload) {
    Dictionary *dict = create_dictionary();
    char *pair_str = strtok(payload, "&");
    while (pair_str != NULL) {
        char *key = strtok(pair_str, "=");
        char *value = strtok(NULL, "=");
        if (key != NULL && value != NULL) {
            add_to_dict(dict, key, value);
        }
        pair_str = strtok(NULL, "&");
    }
    return dict;
}

int main() {
    char url[MAX_URL_LENGTH] = "/api?name=JohnDoe&age=30";
    char *payload = get_payload_from_url(url);
    if (payload != NULL) {
        Dictionary *dict = parse_payload_to_dict(payload);
        char *name = get_from_dict(dict, "name");
        printf("Name: %s\n", name ? name : "Not found");
        free_dictionary(dict);
        free(payload);
    } else {
        printf("No payload found in URL.\n");
    }
    return 0;
}