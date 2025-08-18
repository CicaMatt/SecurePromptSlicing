#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    int count;
    KeyValuePair *items;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->items = NULL;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->count; ++i) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
    free(dict);
}

KeyValuePair* find_in_dict(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; ++i) {
        if (strcmp(dict->items[i].key, key) == 0) {
            return &dict->items[i];
        }
    }
    return NULL;
}

void add_to_dict(Dictionary *dict, const char *key, const char *value) {
    dict->items = realloc(dict->items, sizeof(KeyValuePair) * (dict->count + 1));
    KeyValuePair new_item;
    new_item.key = strdup(key);
    new_item.value = strdup(value);
    dict->items[dict->count++] = new_item;
}

char* get_value_from_dict(Dictionary *dict, const char *key) {
    KeyValuePair *item = find_in_dict(dict, key);
    if (item) {
        return item->value;
    }
    return NULL;
}

void parse_query_string(const char *query, Dictionary *dict) {
    const char *start = query;
    while (*start) {
        const char *equal_sign = strchr(start, '=');
        const char *ampersand = strchr(start, '&');

        if (equal_sign && equal_sign < (ampersand ? ampersand : start + strlen(start))) {
            *equal_sign = '\0';
            add_to_dict(dict, start, equal_sign + 1);

            start = ampersand ? ampersand + 1 : NULL;
        } else {
            break;
        }
    }
}

void handle_request(const char *url) {
    Dictionary *dict = create_dictionary();
    
    const char *payload_start = strstr(url, "?");
    if (payload_start && *(++payload_start)) {
        parse_query_string(payload_start, dict);
    }

    char *name_value = get_value_from_dict(dict, "name");
    if (name_value) {
        printf("Name: %s\n", name_value);
    } else {
        printf("Name not found in payload.\n");
    }

    free_dictionary(dict);
}

int main() {
    const char *url = "/api?payload={\"key\":\"value\",\"name\":\"John Doe\"}";
    handle_request(url);
    
    return 0;
}