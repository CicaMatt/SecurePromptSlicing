#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    size_t size;
    KeyValuePair **items;
} Dictionary;

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->size; ++i) {
        free(dict->items[i]->key);
        free(dict->items[i]->value);
        free(dict->items[i]);
    }
    free(dict->items);
}

int dictionary_add(Dictionary *dict, const char *key, const char *value) {
    KeyValuePair *item = malloc(sizeof(KeyValuePair));
    if (!item) return -1;
    
    item->key = strdup(key);
    item->value = strdup(value);

    dict->size++;
    dict->items = realloc(dict->items, dict->size * sizeof(KeyValuePair *));
    if (!dict->items) {
        free(item->key);
        free(item->value);
        free(item);
        return -1;
    }

    dict->items[dict->size - 1] = item;
    return 0;
}

char* dictionary_get(const Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->size; ++i) {
        if (strcmp(dict->items[i]->key, key) == 0) {
            return dict->items[i]->value;
        }
    }
    return NULL;
}

int parse_payload(Dictionary *dict, const char *payload) {
    char *copy = strdup(payload);
    if (!copy) return -1;

    char *token = strtok(copy, "&");
    while (token != NULL) {
        char *equals = strchr(token, '=');
        if (equals) {
            *equals = '\0';
            char *key = token;
            char *value = equals + 1;

            dictionary_add(dict, key, value);
        }
        token = strtok(NULL, "&");
    }

    free(copy);
    return 0;
}

void handle_request(const char *request) {
    Dictionary dict = { .size = 0, .items = NULL };

    const char *payload_start = strstr(request, "payload=");
    if (!payload_start) {
        printf("Payload not found.\n");
        free_dictionary(&dict);
        return;
    }

    payload_start += strlen("payload=");
    parse_payload(&dict, payload_start);

    char *name_value = dictionary_get(&dict, "name");
    if (name_value) {
        printf("%s\n", name_value);
    } else {
        printf("Name not found.\n");
    }

    free_dictionary(&dict);
}

int main() {
    const char *request = "GET /api?payload=name=John+Doe HTTP/1.1";
    handle_request(request);

    return 0;
}