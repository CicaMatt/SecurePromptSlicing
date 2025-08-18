#include <stdio.h>
#include <string.h>

void handle_request(const char *request) {
    const char *field_start = strstr(request, "name=");
    if (field_start == NULL) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Name field not found.");
        return;
    }

    field_start += 5; // Move past "name="
    const char *field_end = strchr(field_start, '&');
    
    if (field_end == NULL) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("%.*s", (int)strlen(field_start), field_start);
    } else {
        int length = field_end - field_start;
        char name[length + 1];
        strncpy(name, field_start, length);
        name[length] = '\0';
        
        printf("Content-Type: text/plain\r\n\r\n");
        printf("%s", name);
    }
}

int main() {
    const char *request = "name=JohnDoe&age=30";
    handle_request(request);
    return 0;
}