#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

typedef struct {
    char url[MAX_URL_LENGTH];
    void (*function)(const char*);
} Route;

void escape(char* output, const char* input) {
    while (*input) {
        switch (*input) {
            case '&': strcpy(output, "&amp;"); break;
            case '<': strcpy(output, "&lt;"); break;
            case '>': strcpy(output, "&gt;"); break;
            case '"': strcpy(output, "&quot;"); break;
            case '\'': strcpy(output, "&#039;"); break;
            default: *output++ = *input; break;
        }
        input++;
    }
    *output = '\0';
}

void hello(const char* username) {
    char safe_username[256];
    escape(safe_username, username);
    
    printf("Hello %s\n", safe_username);
}

int route_handler(const char* url, const Route routes[], int num_routes) {
    for (int i = 0; i < num_routes; ++i) {
        if (strcmp(url, routes[i].url) == 0) {
            routes[i].function(NULL); // Pass any required parameters as needed
            return 1;
        }
    }
    return 0;
}

int main() {
    Route routes[] = { {"//username", hello} };
    
    const char* url = "//username";
    if (!route_handler(url, routes, sizeof(routes)/sizeof(Route))) {
        printf("No handler for URL: %s\n", url);
    }
    
    return 0;
}