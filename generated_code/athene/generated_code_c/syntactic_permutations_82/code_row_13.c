#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair **pairs;
    int count;
} Dictionary;

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair *));
    dict->pairs[dict->count] = malloc(sizeof(KeyValuePair));
    dict->pairs[dict->count]->key = strdup(key);
    dict->pairs[dict->count]->value = strdup(value);
    dict->count++;
}

char *get_value_from_dictionary(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void parse_payload(Dictionary *dict, const char *payload) {
    while (*payload) {
        const char *start = payload;
        while (*payload && *payload != '=' && *payload != '&' && *payload != '\0') {
            ++payload;
        }
        if (*payload == '=') {
            char key[payload - start + 1];
            strncpy(key, start, payload - start);
            key[payload - start] = '\0';
            start = ++payload;
            while (*payload && *payload != '&' && *payload != '\0') {
                ++payload;
            }
            int len = payload - start;
            char value[len + 1];
            strncpy(value, start, len);
            value[len] = '\0';
            add_to_dictionary(dict, key, value);
        }
        if (*payload == '&') {
            ++payload;
        }
    }
}

int main() {
    const char *url_payload = "name=John&age=30";
    Dictionary dict = {NULL, 0};
    parse_payload(&dict, url_payload);

    char *name = get_value_from_dictionary(&dict, "name");
    if (name) {
        printf("%s\n", name);
    } else {
        printf("Name not found\n");
    }

    for (int i = 0; i < dict.count; ++i) {
        free(dict.pairs[i]->key);
        free(dict.pairs[i]->value);
        free(dict.pairs[i]);
    }
    free(dict.pairs);

    return 0;
}