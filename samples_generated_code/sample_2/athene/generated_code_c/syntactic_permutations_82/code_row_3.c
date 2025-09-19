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

Dictionary *parse_payload(const char *payload) {
    Dictionary *dict = create_dictionary();
    const char *start = payload;
    while (*start && *start != '&') {
        const char *equal = strchr(start, '=');
        if (equal == NULL) break;

        int key_len = equal - start;
        char key[key_len + 1];
        strncpy(key, start, key_len);
        key[key_len] = '\0';

        const char *value_start = equal + 1;
        const char *next = strchr(value_start, '&');
        if (next == NULL) {
            add_to_dictionary(dict, key, value_start);
            break;
        }

        int value_len = next - value_start;
        char value[value_len + 1];
        strncpy(value, value_start, value_len);
        value[value_len] = '\0';

        add_to_dictionary(dict, key, value);

        start = next + 1;
    }
    return dict;
}

int main() {
    const char *payload = "name=John&age=30";
    Dictionary *dict = parse_payload(payload);
    char *name = get_from_dictionary(dict, "name");
    printf("%s\n", name ? name : "Name not found");
    free_dictionary(dict);
    return 0;
}