#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

void handle_request(const char *payload) {
    char name_field[] = "name=";
    size_t name_field_len = strlen(name_field);
    const char *start = strstr(payload, name_field);

    if (start != NULL) {
        start += name_field_len;
        const char *end = strchr(start, '&');
        if (end == NULL) {
            printf("%.*s\n", (int)strlen(start), start);
        } else {
            int length = end - start;
            printf("%.*s\n", length, start);
        }
    } else {
        printf("Name field not found.\n");
    }
}

int main() {
    char payload[MAX_PAYLOAD_SIZE];
    fgets(payload, MAX_PAYLOAD_SIZE, stdin);
    handle_request(payload);
    return 0;
}