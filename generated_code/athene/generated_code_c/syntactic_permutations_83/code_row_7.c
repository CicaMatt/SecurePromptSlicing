#include <stdio.h>
#include <string.h>

void handle_request(char *payload) {
    char name_field[] = "name=";
    char *start, *end;
    
    start = strstr(payload, name_field);
    if (start == NULL) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Field 'name' not found.");
        return;
    }
    
    start += strlen(name_field);
    end = strchr(start, '&');
    if (end == NULL) {
        end = strchr(start, '\0');
    }

    printf("Content-Type: text/plain\r\n\r\n");
    printf("%.*s", (int)(end - start), start);
}

int main() {
    char *payload = "name=John Doe&age=30";
    handle_request(payload);
    return 0;
}