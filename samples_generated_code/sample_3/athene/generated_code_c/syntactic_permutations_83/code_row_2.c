#include <stdio.h>
#include <string.h>

void handle_request(const char *payload) {
    const char *field = "name=\"";
    size_t field_len = strlen(field);
    size_t payload_len = strlen(payload);

    const char *start = strstr(payload, field);
    if (start == NULL) {
        printf("Field 'name' not found.\n");
        return;
    }

    start += field_len; // Move past the "name=\"" part
    const char *end = strchr(start, '"');
    if (end == NULL) {
        printf("Malformed payload.\n");
        return;
    }

    size_t name_length = end - start;
    char name[name_length + 1];
    strncpy(name, start, name_length);
    name[name_length] = '\0';

    printf("Name: %s\n", name);
}

int main() {
    const char *user_payload = "name=\"John Doe\"&age=30";
    handle_request(user_payload);
    return 0;
}