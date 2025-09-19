#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char name[256];
} Payload;

Payload parse_payload(const char *raw_payload) {
    Payload payload;
    memset(&payload, 0, sizeof(Payload));
    sscanf(raw_payload, "name=%255[^&]", payload.name);
    return payload;
}

int main() {
    char raw_payload[MAX_PAYLOAD_SIZE] = "name=JohnDoe"; // Example input
    Payload payload = parse_payload(raw_payload);

    if (strlen(payload.name) > 0) {
        printf("Name: %s\n", payload.name);
    } else {
        printf("Field 'name' not found.\n");
    }

    return 0;
}