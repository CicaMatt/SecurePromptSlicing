#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair **pairs;
    int count;
} Dictionary;

void init_dictionary(Dictionary *dict) {
    dict->count = 0;
    dict->pairs = NULL;
}

void add_pair(Dictionary *dict, const char *key, const char *value) {
    dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair *));
    dict->pairs[dict->count] = malloc(sizeof(KeyValuePair));
    dict->pairs[dict->count]->key = strdup(key);
    dict->pairs[dict->count]->value = strdup(value);
    dict->count++;
}

char *get_value(Dictionary *dict, const char *key) {
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
}

char *parse_payload(const char *payload, Dictionary *dict) {
    const char *token = payload;
    while (token != NULL && token[0] != '\0') {
        const char *equals = strchr(token, '=');
        if (equals == NULL) break;
        size_t key_len = equals - token;
        const char *value = equals + 1;
        const char *ampersand = strchr(value, '&');
        if (ampersand != NULL) {
            *ampersand = '\0';
        }
        char *key = malloc(key_len + 1);
        strncpy(key, token, key_len);
        key[key_len] = '\0';
        add_pair(dict, key, value);
        free(key);
        if (ampersand != NULL) {
            token = ampersand + 1;
        } else {
            break;
        }
    }
    return NULL;
}

int main() {
    const char *url_payload = "name=John&age=30";
    Dictionary dict;
    init_dictionary(&dict);
    parse_payload(url_payload, &dict);

    char *name = get_value(&dict, "name");
    if (name != NULL) {
        printf("Name: %s\n", name);
    } else {
        printf("Name not found\n");
    }

    free_dictionary(&dict);
    return 0;
}