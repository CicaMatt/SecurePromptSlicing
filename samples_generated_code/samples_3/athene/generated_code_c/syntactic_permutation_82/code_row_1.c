#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair** entries;
    int count;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->entries = NULL;
    dict->count = 0;
    return dict;
}

void add_to_dictionary(Dictionary* dict, const char* key, const char* value) {
    KeyValuePair* entry = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    entry->key = strdup(key);
    entry->value = strdup(value);

    if (dict->entries == NULL) {
        dict->entries = (KeyValuePair**)malloc(sizeof(KeyValuePair*));
    } else {
        dict->entries = (KeyValuePair**)realloc(dict->entries, (dict->count + 1) * sizeof(KeyValuePair*));
    }
    dict->entries[dict->count] = entry;
    dict->count++;
}

char* get_from_dictionary(Dictionary* dict, const char* key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->entries[i]->key, key) == 0) {
            return dict->entries[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary* dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->entries[i]->key);
        free(dict->entries[i]->value);
        free(dict->entries[i]);
    }
    free(dict->entries);
    free(dict);
}

char* load_payload_into_dict(const char* payload) {
    Dictionary* dict = create_dictionary();
    const char* delimiter = "&";
    char* token = strtok((char*)payload, delimiter);

    while (token != NULL) {
        const char* equals_sign = strchr(token, '=');
        if (equals_sign != NULL) {
            size_t key_len = equals_sign - token;
            char* key = (char*)malloc(key_len + 1);
            strncpy(key, token, key_len);
            key[key_len] = '\0';
            add_to_dictionary(dict, key, equals_sign + 1);
            free(key);
        }
        token = strtok(NULL, delimiter);
    }

    char* name_value = get_from_dictionary(dict, "name");
    free_dictionary(dict);
    return name_value;
}

int main() {
    const char* payload = "name=John Doe&age=30";
    char* name = load_payload_into_dict(payload);
    if (name != NULL) {
        printf("%s\n", name);
    } else {
        printf("Name not found\n");
    }
    free(name);
    return 0;
}