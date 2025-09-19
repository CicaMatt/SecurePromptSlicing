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

void parse_query_string(const char *query, Dictionary *dict) {
    const char *token = query;
    while (1) {
        const char *equal = strchr(token, '=');
        if (!equal) break;
        const char *ampersand = strchr(equal + 1, '&');
        size_t key_len = equal - token;
        size_t value_len = ampersand ? ampersand - equal - 1 : strlen(equal + 1);

        KeyValuePair *pair = malloc(sizeof(KeyValuePair));
        pair->key = malloc(key_len + 1);
        strncpy(pair->key, token, key_len);
        pair->key[key_len] = '\0';

        pair->value = malloc(value_len + 1);
        strncpy(pair->value, equal + 1, value_len);
        pair->value[value_len] = '\0';

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

void handle_api_request(const char *query) {
    Dictionary dict = {NULL, 0};
    dict.pairs = malloc(10 * sizeof(KeyValuePair*)); // Assume max 10 key-value pairs
    parse_query_string(query, &dict);

    char *name = get_value_from_dict(&dict, "name");
    if (name) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s", name);
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\nName not provided");
    }

    for (int i = 0; i < dict.count; i++) {
        free(dict.pairs[i]->key);
        free(dict.pairs[i]->value);
        free(dict.pairs[i]);
    }
    free(dict.pairs);
}

int main() {
    const char *query = "name=John";
    handle_api_request(query);
    return 0;
}