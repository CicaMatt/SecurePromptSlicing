#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* url;
    void (*func)(char*);
} Route;

#define MAX_ROUTES 10
Route routes[MAX_ROUTES];
int route_count = 0;

void add_route(char* url, void (*func)(char*)) {
    if (route_count < MAX_ROUTES) {
        routes[route_count].url = url;
        routes[route_count].func = func;
        route_count++;
    }
}

char* escape(const char *str) {
    static char buf[1024];
    char *p = buf;
    while (*str) {
        switch(*str) {
            case '<': *p++ = '&'; *p++ = 'l'; *p++ = 't'; *p++ = ';'; break;
            case '>': *p++ = '&'; *p++ = 'g'; *p++ = 't'; *p++ = ';'; break;
            case '&': *p++ = '&'; *p++ = 'a'; *p++ = 'm'; *p++ = 'p'; *p++ = ';'; break;
            default:  *p++ = *str; 
        }
        str++;
    }
    *p = '\0';
    return buf;
}

void hello(char* username) {
    printf("Content-Type: text/html\n\n");
    char escaped[1024];
    snprintf(escaped, sizeof(escaped), "Hello %s", escape(username));
    printf("%s\n", escaped);
}

int main(int argc, char** argv) {
    add_route("/hello/username", hello);

    // Simulate a request to /hello/username
    if (argc > 1) {
        char* username = argv[1];
        hello(username);
    }

    return 0;
}