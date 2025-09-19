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

void parse_payload(const char *payload, Dictionary *dict) {
    dict->count = 0;
    dict->pairs = NULL;

    const char *token = payload;
    while (1) {
        // Find the '=' character
        const char *equals = strchr(token, '=');
        if (!equals) break;

        int key_len = equals - token;
        const char *value = equals + 1;

        // Find the '&' character or end of string
        const char *ampersand = strchr(value, '&');
        if (ampersand) {
            int value_len = ampersand - value;
            *ampersand = '\0';
        } else {
            int value_len = strlen(value);
        }

        // Allocate memory for the key-value pair
        KeyValuePair *pair = malloc(sizeof(KeyValuePair));
        pair->key = malloc(key_len + 1);
        strncpy(pair->key, token, key_len);
        pair->key[key_len] = '\0';

        pair->value = malloc(value_len + 1);
        strncpy(pair->value, value, value_len);
        pair->value[value_len] = '\0';

        // Add the pair to the dictionary
        dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair *));
        dict->pairs[dict->count++] = pair;

        if (!ampersand) break;
        token = ampersand + 1;
    }
}

char *get_value_from_dict(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void free_dict(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
}

int main() {
    const char *payload = "name=John&age=30";
    Dictionary dict;
    parse_payload(payload, &dict);

    char *name = get_value_from_dict(&dict, "name");
    if (name) {
        printf("Name: %s\n", name);
    } else {
        printf("Name not found.\n");
    }

    free_dict(&dict);
    return 0;
}