#include <stdio.h>
#include <string.h>

typedef struct {
    char* url;
    char* (*func)(char*);
} Route;

Route routes[10];
int route_count = 0;

void add_route(char* url, char* (*func)(char*)) {
    if (route_count < 10) {
        routes[route_count].url = url;
        routes[route_count].func = func;
        route_count++;
    }
}

char* escape(const char *str) {
    static char escaped[256];
    char *p = escaped;
    while (*str) {
        switch(*str) {
            case '<': *p++ = '&'; *p++ = 'l'; *p++ = 't'; *p++ = ';'; break;
            case '>': *p++ = '&'; *p++ = 'g'; *p++ = 't'; *p++ = ';'; break;
            case '&': *p++ = '&'; *p++ = 'a'; *p++ = 'm'; *p++ = 'p'; *p++ = ';'; break;
            case '"': *p++ = '&'; *p++ = 'q'; *p++ = 'u'; *p++ = 'o'; *p++ = 't'; *p++ = ';'; break;
            default:  *p++ = *str; break;
        }
        str++;
    }
    *p = '\0';
    return escaped;
}

char* hello(char* username) {
    char greeting[128];
    snprintf(greeting, sizeof(greeting), "Hello %s", escape(username));
    return strdup(greeting);
}

int main() {
    add_route("/hello/username", hello);

    // Simulate a request to /hello/username
    char *username = "John Doe";
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, "/hello/username") == 0) {
            char *response = routes[i].func(username);
            printf("%s\n", response);
            free(response);
        }
    }

    return 0;
}