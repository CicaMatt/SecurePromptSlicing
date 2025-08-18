#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *name;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
} Dictionary;

char* get_payload_from_url(const char *url) {
    const char *prefix = "payload=";
    const char *start = strstr(url, prefix);
    if (start == NULL) return NULL;
    start += strlen(prefix);
    char *end = strchr(start, '&');
    size_t len = end ? (size_t)(end - start) : strlen(start);
    char *result = malloc(len + 1);
    strncpy(result, start, len);
    result[len] = '\0';
    return result;
}

Dictionary load_payload_into_dictionary(const char *payload) {
    Dictionary dict;
    dict.count = 0;
    size_t capacity = 10;
    dict.pairs = malloc(capacity * sizeof(KeyValuePair));
    
    const char *start = payload;
    while (*start) {
        if (dict.count >= capacity) {
            capacity *= 2;
            dict.pairs = realloc(dict.pairs, capacity * sizeof(KeyValuePair));
        }
        
        KeyValuePair pair;
        char *equal_sign = strchr(start, '=');
        if (!equal_sign) break;
        
        size_t key_len = equal_sign - start;
        pair.name = malloc(key_len + 1);
        strncpy(pair.name, start, key_len);
        pair.name[key_len] = '\0';
        
        start = equal_sign + 1;
        char *ampersand = strchr(start, '&');
        if (!ampersand) {
            pair.value = strdup(start);
        } else {
            size_t value_len = ampersand - start;
            pair.value = malloc(value_len + 1);
            strncpy(pair.value, start, value_len);
            pair.value[value_len] = '\0';
        }
        
        dict.pairs[dict.count++] = pair;
        start = ampersand ? (ampersand + 1) : NULL;
    }
    
    return dict;
}

const char* get_value_from_dictionary(const Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->count; ++i) {
        if (strcmp(dict->pairs[i].name, key) == 0) {
            return dict->pairs[i].value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; ++i) {
        free((char *)dict->pairs[i].name);
        free((char *)dict->pairs[i].value);
    }
    free(dict->pairs);
}

int main() {
    const char *url = "http://example.com/api?payload=name=John&age=30";
    const char *payload = get_payload_from_url(url);
    
    if (payload) {
        Dictionary dict = load_payload_into_dictionary(payload);
        
        const char *name_value = get_value_from_dictionary(&dict, "name");
        if (name_value) {
            printf("Name: %s\n", name_value);
        } else {
            printf("Name not found in payload.\n");
        }
        
        free_dictionary(&dict);
        free((char *)payload);
    } else {
        printf("Payload not found in URL.\n");
    }

    return 0;
}