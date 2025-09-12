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

Dictionary *create_dictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->pairs = NULL;
    return dict;
}

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair *));
    KeyValuePair *pair = malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);
    dict->pairs[dict->count++] = pair;
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

char *url_decode(const char *str) {
    int len = strlen(str);
    char *decoded = malloc(len + 1);
    for (int i = 0, j = 0; i < len; i++, j++) {
        if (str[i] == '%' && i + 2 < len) {
            sscanf(str + i + 1, "%2x", (unsigned int *)&decoded[j]);
            i += 2;
        } else {
            decoded[j] = str[i];
        }
    }
    decoded[len] = '\0';
    return decoded;
}

void parse_query_string(const char *query, Dictionary *dict) {
    const char *key_start = query;
    for (int i = 0; query[i]; i++) {
        if (query[i] == '=' && key_start < &query[i]) {
            int key_len = i - key_start;
            const char *value_start = &query[i + 1];
            for (; value_start[0] && value_start[0] != '&'; value_start++);
            int value_len = value_start - (&query[i + 1]);
            char *key = malloc(key_len + 1);
            strncpy(key, key_start, key_len);
            key[key_len] = '\0';
            char *value = malloc(value_len + 1);
            strncpy(value, &query[i + 1], value_len);
            value[value_len] = '\0';

            add_to_dictionary(dict, url_decode(key), url_decode(value));

            free(key);
            free(value);

            key_start = value_start + (value_start[0] == '&');
        }
    }
}

int main() {
    const char *url = "http://example.com/?payload=name%3DJohn%26age%3D30";
    const char *query_start = strchr(url, '?') + 1;
    Dictionary *dict = create_dictionary();
    parse_query_string(query_start, dict);

    char *name = get_from_dictionary(dict, "name");
    if (name) {
        printf("Name: %s\n", name);
    } else {
        printf("Name not found.\n");
    }

    free_dictionary(dict);
    return 0;
}