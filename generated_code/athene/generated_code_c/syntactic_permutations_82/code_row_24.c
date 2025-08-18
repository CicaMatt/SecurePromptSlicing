#include <stdio.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

KeyValuePair* parse_query_string(char* query, int* count) {
    *count = 0;
    KeyValuePair* pairs = NULL;
    if (query == NULL || strlen(query) == 0) return pairs;

    char* token = strtok(query, "&");
    while (token != NULL) {
        (*count)++;
        pairs = realloc(pairs, (*count) * sizeof(KeyValuePair));
        char* eq_pos = strchr(token, '=');
        if (eq_pos == NULL) break;
        *eq_pos = '\0';
        pairs[*count - 1].key = token;
        pairs[*count - 1].value = eq_pos + 1;
        token = strtok(NULL, "&");
    }
    return pairs;
}

char* get_name_from_payload(char* payload) {
    int count;
    KeyValuePair* pairs = parse_query_string(payload, &count);
    for (int i = 0; i < count; i++) {
        if (strcmp(pairs[i].key, "name") == 0) {
            char* name = strdup(pairs[i].value);
            free(pairs);
            return name;
        }
    }
    free(pairs);
    return NULL;
}

int main() {
    // Simulate receiving a payload from /api?payload=name=John
    char* query_string = "name=John";
    char* name = get_name_from_payload(query_string);

    if (name != NULL) {
        printf("Name: %s\n", name);
        free(name);
    } else {
        printf("No name found in payload.\n");
    }

    return 0;
}