#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t count;
} Dictionary;

int dictionary_add(Dictionary *dict, const char *key, const char *value) {
    KeyValuePair new_item = {strdup(key), strdup(value)};
    dict->items = realloc(dict->items, (dict->count + 1) * sizeof(KeyValuePair));
    if (!dict->items) return -1;
    dict->items[dict->count++] = new_item;
    return 0;
}

char* dictionary_get(const Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->count; ++i) {
        if (strcmp(dict->items[i].key, key) == 0) {
            return strdup(dict->items[i].value);
        }
    }
    return NULL;
}

void dictionary_free(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; ++i) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
    dict->items = NULL;
    dict->count = 0;
}

int handle_request(const char *payload, Dictionary *dict) {
    if (dictionary_add(dict, "name", payload) != 0) return -1;
    char *name_value = dictionary_get(dict, "name");
    printf("Name: %s\n", name_value ? name_value : "Key not found");
    free(name_value);
    return 0;
}

int main() {
    Dictionary dict = {NULL, 0};
    const char *payload = "John Doe";

    if (handle_request(payload, &dict) == 0) {
        printf("Request handled successfully.\n");
    } else {
        fprintf(stderr, "Error handling request.\n");
    }

    dictionary_free(&dict);
    return 0;
}