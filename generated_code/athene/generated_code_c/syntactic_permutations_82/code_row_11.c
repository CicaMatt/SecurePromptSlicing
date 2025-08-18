#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair** pairs;
    int count;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->pairs = NULL;
    dict->count = 0;
    return dict;
}

void add_to_dictionary(Dictionary* dict, const char* key, const char* value) {
    KeyValuePair* pair = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);
    dict->pairs = realloc(dict->pairs, sizeof(KeyValuePair*) * (dict->count + 1));
    dict->pairs[dict->count++] = pair;
}

char* get_from_dictionary(Dictionary* dict, const char* key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary* dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
    free(dict);
}

Dictionary* parse_payload(const char* payload) {
    Dictionary* dict = create_dictionary();
    const char* token;
    char key[1024];
    char value[1024];

    while ((token = strsep((char**)&payload, "&")) != NULL) {
        if (sscanf(token, "%[^=]=%s", key, value) == 2) {
            add_to_dictionary(dict, key, value);
        }
    }

    return dict;
}

int main() {
    const char* url = "/api?payload=name=value";
    const char* payload_start = strstr(url, "?payload=") + strlen("?payload=");
    
    if (payload_start == NULL || *payload_start == '\0') {
        printf("Invalid URL\n");
        return 1;
    }

    Dictionary* dict = parse_payload(payload_start);
    char* name_value = get_from_dictionary(dict, "name");

    if (name_value != NULL) {
        printf("%s\n", name_value);
    } else {
        printf("Name not found in payload\n");
    }

    free_dictionary(dict);
    return 0;
}