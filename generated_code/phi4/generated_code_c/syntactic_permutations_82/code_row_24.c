#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

// Simple HTTP request parser (very basic and for demonstration purposes only)
typedef struct {
    char method[8];
    char path[256];
    char payload[MAX_PAYLOAD_SIZE];
} HttpRequest;

HttpRequest parse_request(const char *request) {
    HttpRequest req;
    sscanf(request, "%s %s", req.method, req.path);
    
    const char *payload_start = strstr(request, "\r\n\r\n");
    if (payload_start) {
        strcpy(req.payload, payload_start + 4);
    }
    
    return req;
}

void handle_api_route(const HttpRequest *req, char *response, size_t response_size) {
    char name_key[] = "name=";
    char *name_value_start = strstr(req->payload, name_key);
    if (name_value_start) {
        name_value_start += strlen(name_key); // Move to the value part
        char *name_value_end = strchr(name_value_start, '&');
        
        size_t name_length;
        if (name_value_end) {
            name_length = name_value_end - name_value_start;
        } else {
            name_length = strlen(name_value_start);
        }
        
        strncpy(response, name_value_start, name_length);
        response[name_length] = '\0';
    } else {
        snprintf(response, response_size, "Name parameter not found");
    }
}

int main() {
    char request[] =
        "POST /api HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "Content-Length: 13\r\n"
        "\r\n"
        "name=JohnDoe";

    HttpRequest req = parse_request(request);
    
    if (strcmp(req.path, "/api") == 0) {
        char response[256];
        handle_api_route(&req, response, sizeof(response));
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%s", response);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nRoute not found");
    }
    
    return 0;
}