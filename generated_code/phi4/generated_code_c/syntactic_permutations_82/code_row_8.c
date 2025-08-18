#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char key[50];
    char value[50];
} KeyValuePair;

void parse_payload(const char *payload, KeyValuePair *dict, int *size) {
    const char *delimiter = "&";
    char *token;
    char copy[MAX_PAYLOAD_SIZE];
    strcpy(copy, payload);
    
    token = strtok(copy, delimiter);
    while (token != NULL) {
        char *equal_sign = strchr(token, '=');
        if (equal_sign != NULL) {
            *equal_sign = '\0';
            strncpy(dict[*size].key, token, sizeof(dict[*size].key));
            strcpy(dict[*size].value, equal_sign + 1);
            (*size)++;
        }
        token = strtok(NULL, delimiter);
    }
}

void handle_request(const char *url) {
    KeyValuePair dict[10];
    int size = 0;
    
    const char *payload_start = strstr(url, "payload=");
    if (payload_start != NULL) {
        payload_start += strlen("payload=");

        parse_payload(payload_start, dict, &size);
        
        for (int i = 0; i < size; ++i) {
            if (strcmp(dict[i].key, "name") == 0) {
                printf("%s\n", dict[i].value);
                return;
            }
        }
    }
    
    printf("Name not found in payload.\n");
}

int main() {
    const char *url = "http://example.com/api?payload=name=JohnDoe&age=30";
    handle_request(url);
    return 0;
}