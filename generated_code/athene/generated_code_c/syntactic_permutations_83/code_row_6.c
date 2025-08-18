#include <stdio.h>
#include <string.h>

void handle_request(char *payload) {
    char name[256] = "";
    char *field_name = "name=";
    char *value_start = strstr(payload, field_name);
    if (value_start != NULL) {
        value_start += strlen(field_name);
        char *end = strchr(value_start, '&');
        if (end == NULL) {
            strncpy(name, value_start, 255);
        } else {
            int length = end - value_start;
            strncpy(name, value_start, length > 255 ? 255 : length);
            name[length] = '\0';
        }
    }

    if (strlen(name) > 0) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("%s", name);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Name field not found.");
    }
}

int main() {
    char *payload = getenv("QUERY_STRING"); // Assuming CGI environment
    if (payload == NULL) payload = "";
    handle_request(payload);

    return 0;
}