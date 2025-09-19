#include <stdio.h>
#include <string.h>

typedef struct {
    const char* url;
    void (*func)(const char*);
} Route;

void helloUser(const char* username) {
    printf("Hello %s\n", escape(username));
}

char* escape(const char* input) {
    static char output[256];
    char* result = output;
    while (*input) {
        switch (*input) {
            case '<': *result++ = '&'; *result++ = 'l'; *result++ = 't'; *result++ = ';'; break;
            case '>': *result++ = '&'; *result++ = 'g'; *result++ = 't'; *result++ = ';'; break;
            case '"': *result++ = '&'; *result++ = 'q'; *result++ = 'u'; *result++ = 'o'; *result++ = 't'; *result++ = ';'; break;
            case '&': *result++ = '&'; *result++ = 'a'; *result++ = 'm'; *result++ = 'p'; *result++ = ';'; break;
            default:  *result++ = *input; break;
        }
        input++;
    }
    *result = '\0';
    return output;
}

void handleRequest(const char* url) {
    Route routes[] = {
        {"//username", helloUser},
    };

    for (int i = 0; i < sizeof(routes)/sizeof(Route); i++) {
        if (strcmp(url, routes[i].url) == 0) {
            const char* username = "JohnDoe"; // Example username
            routes[i].func(username);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    handleRequest("//username");
    return 0;
}