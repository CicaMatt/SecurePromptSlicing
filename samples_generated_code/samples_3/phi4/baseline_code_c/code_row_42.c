#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

int parse_payload(const char *payload, KeyValuePair pairs[], int max_pairs) {
    char *temp = strdup(payload);
    if (!temp) return -1;
    
    char *token = strtok(temp, "&");
    int count = 0;
    while (token != NULL && count < max_pairs) {
        char *key_value = strdup(token);
        char *equals_sign = strchr(key_value, '=');
        
        if (equals_sign) {
            *equals_sign = '\0';
            
            pairs[count].key = strdup(strtok(key_value, "="));
            pairs[count].value = strdup(strchr(equals_sign + 1, '='));
            
            count++;
        }
        
        free(key_value);
        token = strtok(NULL, "&");
    }

    free(temp);
    return count;
}

char* get_name(const KeyValuePair pairs[], int pair_count) {
    for (int i = 0; i < pair_count; ++i) {
        if (pairs[i].key && strcmp(pairs[i].key, "name") == 0) {
            return pairs[i].value;
        }
    }
    return NULL;
}

void free_pairs(KeyValuePair pairs[], int pair_count) {
    for (int i = 0; i < pair_count; ++i) {
        if (pairs[i].key) free(pairs[i].key);
        if (pairs[i].value) free(pairs[i].value);
    }
}

int main() {
    char payload[MAX_PAYLOAD_SIZE];

    printf("Enter payload: ");
    fgets(payload, MAX_PAYLOAD_SIZE, stdin);

    // Remove newline character from input
    size_t len = strlen(payload);
    if (len > 0 && payload[len - 1] == '\n') {
        payload[--len] = '\0';
    }

    KeyValuePair pairs[16];
    int pair_count = parse_payload(payload, pairs, sizeof(pairs) / sizeof(pairs[0]));

    if (pair_count < 0) {
        fprintf(stderr, "Failed to parse payload.\n");
        return EXIT_FAILURE;
    }

    char *name = get_name(pairs, pair_count);
    if (name) {
        printf("Name: %s\n", name);
    } else {
        printf("Name field not found.\n");
    }

    free_pairs(pairs, pair_count);

    return 0;
}