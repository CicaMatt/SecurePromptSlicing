#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    dict->pairs = NULL;
    dict->count = 0;
    return dict;
}

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    dict->pairs = (KeyValuePair *)realloc(dict->pairs, sizeof(KeyValuePair) * (dict->count + 1));
    dict->pairs[dict->count].key = strdup(key);
    dict->pairs[dict->count].value = strdup(value);
    dict->count++;
}

const char* get_value_from_dictionary(Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->count; ++i) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            return dict->pairs[i].value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; ++i) {
        free((void *)dict->pairs[i].key);
        free((void *)dict->pairs[i].value);
    }
    free(dict->pairs);
    free(dict);
}

char* parse_payload(const char *payload) {
    Dictionary *dict = create_dictionary();
    const char *delim = "&";
    char *token, *rest = strdup(payload), *temp;
    
    token = strtok_r(rest, delim, &rest);
    while (token != NULL) {
        temp = strchr(token, '=');
        if (temp != NULL) {
            *temp = '\0';
            add_to_dictionary(dict, token, temp + 1);
        }
        token = strtok_r(NULL, delim, &rest);
    }

    const char *name_value = get_value_from_dictionary(dict, "name");
    char *result = name_value ? strdup(name_value) : strdup("Name not found");

    free(rest);
    free_dictionary(dict);

    return result;
}

const char* handle_request(const char *url) {
    const char *start = strstr(url, "?payload=");
    if (start == NULL) {
        return "Invalid request";
    }
    start += strlen("?payload=");

    char *payload = strndup(start, MAX_PAYLOAD_SIZE);
    char *response = parse_payload(payload);
    free(payload);

    return response;
}

int main() {
    const char *url = "http://example.com/api?payload=name=JohnDoe&age=30";
    printf("Response: %s\n", handle_request(url));
    return 0;
}