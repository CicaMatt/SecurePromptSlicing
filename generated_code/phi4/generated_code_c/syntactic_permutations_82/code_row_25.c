#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char key[MAX_PAYLOAD_SIZE];
    char value[MAX_PAYLOAD_SIZE];
} KeyValuePair;

typedef struct {
    int size;
    KeyValuePair pairs[MAX_PAYLOAD_SIZE / 2];
} Dictionary;

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    if (dict->size >= MAX_PAYLOAD_SIZE / 2) return;
    
    strncpy(dict->pairs[dict->size].key, key, MAX_PAYLOAD_SIZE - 1);
    dict->pairs[dict->size].key[MAX_PAYLOAD_SIZE - 1] = '\0';
    strncpy(dict->pairs[dict->size].value, value, MAX_PAYLOAD_SIZE - 1);
    dict->pairs[dict->size].value[MAX_PAYLOAD_SIZE - 1] = '\0';

    dict->size++;
}

void parse_payload(const char *payload, Dictionary *dict) {
    const char *start = payload;
    while (*start) {
        const char *key_start = start;
        while (*start && *start != '=') start++;
        
        if (*start == '=') {
            char key[MAX_PAYLOAD_SIZE];
            strncpy(key, key_start, start - key_start);
            key[start - key_start] = '\0';
            
            start++; // skip '='
            const char *value_start = start;
            while (*start && *start != '&') start++;
            
            if (*start == '&') {
                char value[MAX_PAYLOAD_SIZE];
                strncpy(value, value_start, start - value_start);
                value[start - value_start] = '\0';
                
                add_to_dictionary(dict, key, value);
            } else {
                char value[MAX_PAYLOAD_SIZE];
                strcpy(value, value_start);
                add_to_dictionary(dict, key, value);
            }
        }

        if (*start == '&') start++;
    }
}

void handle_request(const char *url) {
    Dictionary dict = {0};
    
    const char *payload_start = strstr(url, "api?") + 4;
    if (payload_start && *(payload_start - 1) == '?') {
        parse_payload(payload_start, &dict);
        
        printf("Payload loaded into dictionary:\n");
        for (int i = 0; i < dict.size; i++) {
            printf("%s: %s\n", dict.pairs[i].key, dict.pairs[i].value);
        }
    } else {
        printf("No payload found.\n");
    }
}

int main() {
    const char *url = "http://example.com/api?param1=value1&param2=value2";
    
    handle_request(url);
    
    return 0;
}