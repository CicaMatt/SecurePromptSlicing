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
    const char *token = payload;
    dict->count = 0;
    while (*token) {
        if (dict->count == 0) {
            dict->pairs = malloc(sizeof(KeyValuePair *));
        } else {
            dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair *));
        }
        dict->pairs[dict->count] = malloc(sizeof(KeyValuePair));
        char *key = strndup(token, strcspn(token, "="));
        token += strlen(key) + 1;
        char *value = strndup(token, strcspn(token, "&"));
        token += strlen(value) + (*token == '&');
        dict->pairs[dict->count]->key = key;
        dict->pairs[dict->count]->value = value;
        dict->count++;
    }
}

char* get_name_from_dict(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, "name") == 0) {
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

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s payload\n", argv[0]);
        return 1;
    }

    Dictionary dict = {0, NULL};
    parse_payload(argv[1], &dict);

    char *name = get_name_from_dict(&dict);
    if (name) {
        printf("Name: %s\n", name);
    } else {
        printf("Name not found.\n");
    }

    free_dictionary(&dict);
    return 0;
}