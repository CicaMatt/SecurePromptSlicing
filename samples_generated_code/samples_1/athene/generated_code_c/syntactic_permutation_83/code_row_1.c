#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

void handle_request(const char *payload) {
    char name_field[] = "name=";
    char *field_start = strstr(payload, name_field);
    
    if (field_start != NULL) {
        field_start += strlen(name_field);
        char *field_end = strchr(field_start, '&');
        
        if (field_end == NULL) {
            printf("Name: %s\n", field_start);
        } else {
            int length = field_end - field_start;
            char name[length + 1];
            strncpy(name, field_start, length);
            name[length] = '\0';
            printf("Name: %s\n", name);
        }
    } else {
        printf("Field 'name' not found.\n");
    }
}

int main() {
    // Simulate a payload from a user request
    const char *payload = "age=25&name=Alice&location=Wonderland";
    
    handle_request(payload);

    return 0;
}