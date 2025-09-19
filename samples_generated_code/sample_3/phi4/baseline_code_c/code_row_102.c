#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char name[BUFFER_SIZE];
} Payload;

Payload parse_payload(const char *request) {
    Payload payload = {0};
    const char *token_name = "name=";
    
    if (strstr(request, token_name)) {
        char *start_ptr = strstr(request, token_name);
        
        start_ptr += strlen(token_name); // Move past 'name='
        char *end_ptr = strchr(start_ptr, '&');
        size_t len = end_ptr ? end_ptr - start_ptr : strlen(start_ptr);

        if (len < BUFFER_SIZE) {
            strncpy(payload.name, start_ptr, len);
            payload.name[len] = '\0';
        }
    }

    return payload;
}

void handle_request(const char *request) {
    Payload payload = parse_payload(request);
    
    if (strlen(payload.name) > 0) {
        printf("Name: %s\n", payload.name);
    } else {
        printf("No name field found.\n");
    }
}

int main() {
    const char *user_request = "GET / HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\nname=JohnDoe&age=30";
    
    handle_request(user_request);
    
    return 0;
}