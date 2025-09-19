#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

void process_request(const char *payload) {
    const char *name_start = strstr(payload, "\"name\":\"");
    
    if (name_start != NULL) {
        name_start += strlen("\"name\":\"");
        const char *name_end = strchr(name_start, '"');
        
        if (name_end != NULL) {
            size_t name_length = name_end - name_start;
            char name[name_length + 1];
            strncpy(name, name_start, name_length);
            name[name_length] = '\0';
            
            printf("Name: %s\n", name);
        } else {
            printf("Invalid payload format.\n");
        }
    } else {
        printf("Field 'name' not found.\n");
    }
}

int main() {
    char payload[MAX_PAYLOAD_SIZE];
    
    printf("Enter JSON payload:\n");
    if (fgets(payload, MAX_PAYLOAD_SIZE, stdin) != NULL) {
        process_request(payload);
    }

    return 0;
}