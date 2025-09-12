#include <stdio.h>
#include <string.h>

void handle_request(const char *payload) {
    const char *field_name = "name";
    size_t payload_len = strlen(payload);
    size_t field_name_len = strlen(field_name);

    if (payload_len >= field_name_len + 5 && 
        strncmp(payload, "{\"name\":\"", field_name_len + 7) == 0 &&
        strstr(payload, "\"}") != NULL) {
        
        const char *start = payload + field_name_len + 2;
        size_t content_len = strlen(start);
        if (content_len > 1 && start[content_len - 1] == '\"') {
            content_len--;
            printf("Name: %.*s\n", (int)content_len, start);
            return;
        }
    }

    // If the field 'name' does not exist or is malformed
    printf("Field 'name' not found or invalid format.\n");
}

int main() {
    const char *request_payload = "{\"name\":\"John Doe\"}";
    handle_request(request_payload);
    return 0;
}