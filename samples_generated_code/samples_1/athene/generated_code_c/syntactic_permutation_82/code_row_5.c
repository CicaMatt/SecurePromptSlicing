#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    int count;
    KeyValuePair** pairs;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->pairs = NULL;
    return dict;
}

void add_to_dictionary(Dictionary* dict, const char* key, const char* value) {
    KeyValuePair* pair = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);

    dict->count++;
    dict->pairs = (KeyValuePair**)realloc(dict->pairs, dict->count * sizeof(KeyValuePair*));
    dict->pairs[dict->count - 1] = pair;
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

char* parse_payload(const char* payload) {
    Dictionary* dict = create_dictionary();
    const char* token;
    char key[256], value[256];
    while ((token = strsep((char**)&payload, "&")) != NULL) {
        if (sscanf(token, "%[^=]=%s", key, value) == 2) {
            add_to_dictionary(dict, key, value);
        }
    }

    char* name_value = get_from_dictionary(dict, "name");
    free_dictionary(dict);

    return name_value;
}

int main() {
    const char* url_payload = "payload=name=John&age=30";
    const char* payload_start = strchr(url_payload, '=') + 1;

    char* name = parse_payload(payload_start);
    if (name != NULL) {
        printf("Name: %s\n", name);
        free(name); // Assuming strdup was used
    } else {
        printf("Name not found.\n");
    }

    return 0;
}