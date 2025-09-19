#include <stdio.h>
#include <string.h>

typedef struct {
    const char* url;
    void (*handler)(const char*);
} Route;

#define NUM_ROUTES 1

Route routes[NUM_ROUTES] = {{"", NULL}};

void escape(char *dest, const char *src) {
    while (*src) {
        switch (*src) {
            case '<': strcat(dest, "&lt;"); break;
            case '>': strcat(dest, "&gt;"); break;
            case '&': strcat(dest, "&amp;"); break;
            case '"': strcat(dest, "&quot;"); break;
            default: *dest++ = *src;
        }
        src++;
    }
    *dest = '\0';
}

void hello(const char* username) {
    char safe_username[1024] = "";
    escape(safe_username, username);
    printf("Hello %s\n", safe_username);
}

void route_dispatch(const char* url) {
    const char* username = url + 7; // Skip "/hello/"
    if (url[6] == '\0') { // No username provided
        return;
    }
    hello(username);
}

int main(int argc, char** argv) {
    if (argc != 2) return 1;
    route_dispatch(argv[1]);
    return 0;
}