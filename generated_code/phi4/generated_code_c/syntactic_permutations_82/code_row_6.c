#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char name[MAX_PAYLOAD_SIZE];
} Payload;

int main() {
    char url[] = "http://example.com/api?payload=%7B%22name%22%3A%22JohnDoe%22%7D";
    char *start, *end;
    char payload[MAX_PAYLOAD_SIZE] = {0};

    // Extracting the query string
    start = strstr(url, "?");
    if (start) {
        start += 1; // Move past '?'
        end = strchr(start, '&');
        if (!end || strlen(end) == 0) {
            strncpy(payload, start, MAX_PAYLOAD_SIZE - 1);
        } else {
            strncpy(payload, start, end - start);
        }
    }

    char *decodedPayload;
    asprintf(&decodedPayload, "%s", payload);

    // Convert URL-encoded string to regular string
    for (char *p = decodedPayload; *p; ++p) {
        if (*p == '%') {
            int value;
            sscanf(p + 1, "%2x", &value);
            *p = value;
            memmove(p + 1, p + 3, strlen(p + 3) + 1);
        }
    }

    Payload myPayload;
    sscanf(decodedPayload, "{\"name\":\"%[^\"]\"}", myPayload.name);

    printf("Name: %s\n", myPayload.name);

    free(decodedPayload);
    return 0;
}