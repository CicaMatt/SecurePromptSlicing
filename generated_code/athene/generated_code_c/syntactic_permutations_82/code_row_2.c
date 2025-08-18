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

Dictionary *create_dictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->pairs = NULL;
    dict->count = 0;
    return dict;
}

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    KeyValuePair *pair = malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);

    dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair *));
    dict->pairs[dict->count] = pair;
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

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
    free(dict);
}

char *parse_payload(const char *payload) {
    Dictionary *dict = create_dictionary();
    const char *start = payload;
    while (*payload) {
        if (*payload == '&' || *payload == '\0') {
            const char *eq = strchr(start, '=');
            if (eq && eq < payload) {
                int key_len = eq - start;
                int value_len = payload - eq - 1;
                char *key = malloc(key_len + 1);
                strncpy(key, start, key_len);
                key[key_len] = '\0';
                char *value = malloc(value_len + 1);
                strncpy(value, eq + 1, value_len);
                value[value_len] = '\0';
                add_to_dictionary(dict, key, value);
                free(key);
                free(value);
            }
            start = payload + 1;
        }
        payload++;
    }

    char *name = get_from_dictionary(dict, "name");
    free_dictionary(dict);
    return name;
}

int main() {
    const char *payload = "payload=name=JohnDoe";
    char *name = parse_payload(strstr(payload, "=") + 1);
    if (name != NULL) {
        printf("Name: %s\n", name);
        free(name);
    } else {
        printf("Name not found\n");
    }
    return 0;
}