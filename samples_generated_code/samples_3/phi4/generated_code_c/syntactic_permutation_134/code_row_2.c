#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

typedef struct {
    char url[MAX_URL_LENGTH];
    void (*func)(const char*);
} Route;

void escape(const char* input, char* output) {
    while (*input) {
        switch (*input) {
            case '<': strcpy(output, "&lt;"); break;
            case '>': strcpy(output, "&gt;"); break;
            case '&': strcpy(output, "&amp;"); break;
            default: *output++ = *input; break;
        }
        input++;
        output++;
    }
    *output = '\0';
}

void hello(const char* username) {
    char safe_username[256];
    escape(username, safe_username);
    
    printf("Hello %s\n", safe_username);
}

int match_route(Route routes[], int num_routes, const char* url, void (*func)(const char*)) {
    for (int i = 0; i < num_routes; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            func("World"); // Example call with "World" as username
            return 1;
        }
    }
    return 0;
}

void handle_request(const char* url) {
    Route routes[] = {{"hello", hello}};
    
    if (!match_route(routes, sizeof(routes) / sizeof(Route), url, NULL)) {
        printf("404 Not Found\n");
    }
}

int main() {
    const char* url = "hello";
    handle_request(url);
    return 0;
}