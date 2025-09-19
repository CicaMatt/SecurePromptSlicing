#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char **keys;
    char **values;
    size_t count;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->keys = NULL;
    dict->values = NULL;
    dict->count = 0;
    return dict;
}

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    size_t new_count = dict->count + 1;
    dict->keys = realloc(dict->keys, new_count * sizeof(char *));
    dict->values = realloc(dict->values, new_count * sizeof(char *));
    
    dict->keys[dict->count] = strdup(key);
    dict->values[dict->count] = strdup(value);
    dict->count++;
}

char* get_value_from_dictionary(Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->count; i++) {
        if (strcmp(dict->keys[i], key) == 0) {
            return dict->values[i];
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; i++) {
        free(dict->keys[i]);
        free(dict->values[i]);
    }
    free(dict->keys);
    free(dict->values);
    free(dict);
}

void handle_request(const char *payload) {
    Dictionary *dict = create_dictionary();
    
    const char *key_value_separator = "=";
    const char *entry_separator = "&";
    char *entry_copy = strdup(payload);

    char *entry = strtok(entry_copy, entry_separator);
    while (entry != NULL) {
        char *key = strtok(entry, key_value_separator);
        if (key) {
            char *value = strtok(NULL, key_value_separator);
            if (value) {
                add_to_dictionary(dict, key, value);
            }
        }
        entry = strtok(NULL, entry_separator);
    }

    free(entry_copy);

    const char *name_key = "name";
    char *name_value = get_value_from_dictionary(dict, name_key);
    if (name_value != NULL) {
        printf("Name: %s\n", name_value);
    } else {
        printf("Name not found in payload.\n");
    }

    free_dictionary(dict);
}

int main() {
    const char *url_payload = "name=JohnDoe&age=30";
    
    // Simulate the /api route handling
    handle_request(url_payload);

    return 0;
}