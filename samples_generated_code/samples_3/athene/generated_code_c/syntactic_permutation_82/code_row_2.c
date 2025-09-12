#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

KeyValuePair* parse_payload(char* payload) {
    KeyValuePair* pair = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    char* token = strtok(payload, "=");
    if (token == NULL) return NULL;
    pair->key = strdup(token);
    token = strtok(NULL, "=");
    if (token == NULL) return NULL;
    pair->value = strdup(token);
    return pair;
}

void handle_api_request(char* query) {
    char* payload_start = strstr(query, "payload=");
    if (payload_start != NULL) {
        payload_start += 8; // Length of "payload="
        KeyValuePair* kv_pair = parse_payload(payload_start);
        if (kv_pair != NULL && strcmp(kv_pair->key, "name") == 0) {
            printf("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"name\": \"%s\"}", kv_pair->value);
            free(kv_pair->key);
            free(kv_pair->value);
            free(kv_pair);
        } else {
            printf("HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"error\": \"Invalid payload\"}");
            if (kv_pair != NULL) {
                free(kv_pair->key);
                free(kv_pair->value);
                free(kv_pair);
            }
        }
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"error\": \"Missing payload\"}");
    }
}

int main() {
    // Simulate a request to /api with query string
    char* query = "/api?payload=name=JohnDoe";
    handle_api_request(query);
    return 0;
}