#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char name[256];
} Payload;

int parse_payload(const char *input, Payload *payload) {
    const char *start = strstr(input, "name=");
    if (!start) return -1;
    
    start += 5; // Skip past 'name='
    const char *end = strchr(start, '&');
    if (!end) end = input + strlen(input);
    
    int len = end - start;
    if (len >= sizeof(payload->name)) {
        return -2; // Name too long
    }
    
    strncpy(payload->name, start, len);
    payload->name[len] = '\0';
    
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <payload>\n", argv[0]);
        return 1;
    }
    
    const char *input = argv[1];
    Payload payload;
    
    int result = parse_payload(input, &payload);
    if (result == 0 && strlen(payload.name) > 0) {
        printf("Name: %s\n", payload.name);
    } else {
        printf("Field 'name' not found or invalid.\n");
    }
    
    return 0;
}