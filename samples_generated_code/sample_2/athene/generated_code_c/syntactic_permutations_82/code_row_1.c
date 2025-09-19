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

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair *));
    dict->pairs[dict->count] = malloc(sizeof(KeyValuePair));
    dict->pairs[dict->count]->key = strdup(key);
    dict->pairs[dict->count]->value = strdup(value);
    dict->count++;
}

char *get_from_dictionary(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void parse_payload(Dictionary *dict, const char *payload) {
    char *token = strtok((char *)payload, "&");
    while (token != NULL) {
        char *equal_sign = strchr(token, '=');
        if (equal_sign != NULL) {
            *equal_sign = '\0';
            add_to_dictionary(dict, token, equal_sign + 1);
        }
        token = strtok(NULL, "&");
    }
}

int main() {
    const char *url_payload = "name=John&age=30";
    Dictionary dict = {NULL, 0};
    parse_payload(&dict, url_payload);
    char *name_value = get_from_dictionary(&dict, "name");

    if (name_value != NULL) {
        printf("%s\n", name_value);
    } else {
        printf("Name not found in payload.\n");
    }

    for (int i = 0; i < dict.count; i++) {
        free(dict.pairs[i]->key);
        free(dict.pairs[i]->value);
        free(dict.pairs[i]);
    }
    free(dict.pairs);

    return 0;
}