#include <stdio.h>
#include <string.h>

void handle_request(const char *payload) {
    const char *field = "name=\"";
    const size_t field_len = strlen(field);
    const size_t payload_len = strlen(payload);

    for (size_t i = 0; i <= payload_len - field_len; ++i) {
        if (strncmp(payload + i, field, field_len) == 0) {
            const char *start = payload + i + field_len;
            const char *end = strchr(start, '\"');
            if (end != NULL) {
                size_t name_len = end - start;
                char name[name_len + 1];
                strncpy(name, start, name_len);
                name[name_len] = '\0';
                printf("Content-Type: text/plain\r\n\r\n");
                printf("%s", name);
                return;
            }
        }
    }

    printf("Content-Type: text/plain\r\n\r\n");
    printf("Field 'name' not found.");
}

int main() {
    const char *request_payload = "field1=value1&name=John%20Doe&field2=value2";
    handle_request(request_payload);
    return 0;
}