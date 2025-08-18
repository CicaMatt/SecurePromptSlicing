#include <stdio.h>
#include <string.h>

char* get_name_field(const char* payload) {
    const char *field = "name=";
    const size_t field_len = strlen(field);
    const size_t payload_len = strlen(payload);

    for (size_t i = 0; i <= payload_len - field_len; ++i) {
        if (strncmp(payload + i, field, field_len) == 0) {
            const char *start = payload + i + field_len;
            const char *end = strchr(start, '&');
            if (end == NULL) {
                end = payload + payload_len;
            }
            size_t name_len = end - start;
            char *name = malloc(name_len + 1);
            if (name != NULL) {
                strncpy(name, start, name_len);
                name[name_len] = '\0';
                return name;
            }
        }
    }

    return NULL;
}

int main() {
    const char* payload = "id=123&name=John%20Doe&age=30";
    char* name = get_name_field(payload);
    if (name != NULL) {
        printf("%s\n", name);
        free(name);
    } else {
        printf("Field 'name' not found.\n");
    }
    return 0;
}