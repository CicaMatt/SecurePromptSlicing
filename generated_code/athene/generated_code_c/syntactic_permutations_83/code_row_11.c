#include <stdio.h>
#include <string.h>

void handle_request(const char *payload) {
    const char *field = "name=";
    int field_len = 5;
    char name[1024] = "";
    const char *start, *end;

    start = strstr(payload, field);
    if (start == NULL) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Field 'name' not found.");
        return;
    }

    start += field_len; // Move past "name="
    end = strchr(start, '&');
    if (end == NULL) {
        strncpy(name, start, sizeof(name) - 1);
    } else {
        int len = end - start;
        strncpy(name, start, len);
        name[len] = '\0';
    }

    printf("Content-Type: text/plain\r\n\r\n");
    printf("%s", name);
}

int main() {
    const char *payload = "name=John Doe&age=30"; // Example payload
    handle_request(payload);
    return 0;
}