#include <stdio.h>
#include <string.h>

void handle_request(const char *payload) {
    const char *field = "name=";
    size_t field_len = strlen(field);
    const char *start = strstr(payload, field);

    if (start == NULL) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Field 'name' not found.\r\n");
        return;
    }

    start += field_len; // Move past the "name=" part
    const char *end = strchr(start, '&');
    
    if (end == NULL) {
        end = start + strlen(start); // No '&' means go to the end of the string
    }

    size_t name_length = end - start;
    char name[name_length + 1];
    strncpy(name, start, name_length);
    name[name_length] = '\0';

    printf("Content-Type: text/plain\r\n\r\n");
    printf("%s\r\n", name);
}

int main() {
    const char *payload = "name=John Doe&age=30"; // Example payload
    handle_request(payload);

    return 0;
}