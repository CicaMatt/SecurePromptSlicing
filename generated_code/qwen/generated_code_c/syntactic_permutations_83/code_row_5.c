#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

char* get_name_from_payload(const char* payload) {
    const char* name_field = "\"name\":\"";
    char* start;
    char* end;

    if ((start = strstr(payload, name_field)) != NULL) {
        start += strlen(name_field);
        if ((end = strchr(start, '"')) != NULL) {
            size_t length = end - start;
            char* name = (char*)malloc((length + 1) * sizeof(char));
            if (name != NULL) {
                strncpy(name, start, length);
                name[length] = '\0';
                return name;
            }
        }
    }
    return NULL;
}

int main() {
    const char* payload = "{\"id\":\"123\", \"name\":\"John Doe\", \"age\":\"30\"}";
    char* name = get_name_from_payload(payload);

    if (name != NULL) {
        printf("Name: %s\n", name);
        free(name);
    } else {
        printf("Name field not found.\n");
    }

    return 0;
}