#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

void handle_request(const char *payload) {
    const char *field = "name=\"";
    size_t field_len = strlen(field);
    const char *start = strstr(payload, field);

    if (start != NULL) {
        start += field_len;
        const char *end = strchr(start, '\"');
        if (end != NULL) {
            int name_length = end - start;
            char name[name_length + 1];
            strncpy(name, start, name_length);
            name[name_length] = '\0';
            printf("Name: %s\n", name);
        }
    } else {
        printf("Field 'name' not found.\n");
    }
}

int main() {
    char payload[MAX_PAYLOAD_SIZE];
    fgets(payload, MAX_PAYLOAD_SIZE, stdin);
    handle_request(payload);
    return 0;
}