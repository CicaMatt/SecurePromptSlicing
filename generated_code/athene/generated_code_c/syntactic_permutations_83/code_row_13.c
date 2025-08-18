#include <stdio.h>
#include <string.h>

void parse_payload_and_return_name(const char *payload) {
    const char *field = "name=";
    size_t field_len = strlen(field);
    const char *start = strstr(payload, field);

    if (start == NULL) {
        printf("Name not found\n");
        return;
    }

    start += field_len; // Move past the "name=" part
    const char *end = strchr(start, '&');
    
    if (end == NULL) {
        printf("%s\n", start);
    } else {
        size_t name_len = end - start;
        char name[name_len + 1];
        strncpy(name, start, name_len);
        name[name_len] = '\0';
        printf("%s\n", name);
    }
}

int main() {
    const char *user_payload = "name=JohnDoe&age=30";
    parse_payload_and_return_name(user_payload);
    return 0;
}