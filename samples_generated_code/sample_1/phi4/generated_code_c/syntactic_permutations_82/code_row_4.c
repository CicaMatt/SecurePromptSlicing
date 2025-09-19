#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char name[MAX_PAYLOAD_SIZE];
} Dictionary;

void process_request(const char *payload) {
    Dictionary dict;
    sscanf(payload, "name=%s", dict.name);
    printf("Name: %s\n", dict.name);
}

int main() {
    const char *url = "http://localhost/api?payload=name=JohnDoe";
    
    // Extract payload from URL
    char *payload_str = strstr(url, "payload=");
    if (payload_str) {
        payload_str += 8; // Move past 'payload='
        char payload[MAX_PAYLOAD_SIZE];
        strncpy(payload, payload_str, MAX_PAYLOAD_SIZE - 1);
        payload[MAX_PAYLOAD_SIZE - 1] = '\0';
        
        process_request(payload);
    } else {
        printf("Payload not found in the URL.\n");
    }
    
    return 0;
}