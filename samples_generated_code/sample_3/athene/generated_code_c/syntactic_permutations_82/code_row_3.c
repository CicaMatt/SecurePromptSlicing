#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair** pairs;
    int count;
} Dictionary;

void parse_query_string(const char* query, Dictionary* dict) {
    const char* token = strtok((char*)query, "&");
    while (token != NULL) {
        char* equal_sign = strchr(token, '=');
        if (equal_sign != NULL) {
            *equal_sign = '\0';
            KeyValuePair* pair = malloc(sizeof(KeyValuePair));
            pair->key = strdup(token);
            pair->value = strdup(equal_sign + 1);
            dict->pairs[dict->count++] = pair;
        }
        token = strtok(NULL, "&");
    }
}

char* get_value_from_dict(Dictionary* dict, const char* key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void free_dict(Dictionary* dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
}

int main() {
    const char* query = "payload={%22name%22:%22John%20Doe%22}";
    Dictionary dict;
    dict.pairs = malloc(10 * sizeof(KeyValuePair*));
    dict.count = 0;

    parse_query_string(query, &dict);
    char* name = get_value_from_dict(&dict, "name");

    if (name != NULL) {
        printf("Name: %s\n", name);
    } else {
        printf("Name not found.\n");
    }

    free_dict(&dict);
    return 0;
}