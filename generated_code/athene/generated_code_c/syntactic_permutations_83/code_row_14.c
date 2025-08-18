#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

void handle_request(const char *payload) {
    char name[MAX_PAYLOAD_SIZE] = "";
    const char *start = strstr(payload, "name=");
    if (start != NULL) {
        start += 5; // Skip "name="
        const char *end = strchr(start, '&');
        if (end == NULL) {
            strncpy(name, start, MAX_PAYLOAD_SIZE - 1);
        } else {
            size_t len = end - start;
            strncpy(name, start, len < MAX_PAYLOAD_SIZE - 1 ? len : MAX_PAYLOAD_SIZE - 1);
        }
    }

    if (name[0] != '\0') {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("%s", name);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Name not found in payload.");
    }
}

int main() {
    char payload[MAX_PAYLOAD_SIZE];
    fgets(payload, MAX_PAYLOAD_SIZE, stdin);
    handle_request(payload);
    return 0;
}