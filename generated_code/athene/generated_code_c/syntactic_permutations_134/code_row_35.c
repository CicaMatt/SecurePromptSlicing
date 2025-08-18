#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*func)(const char*);
} RouteHandler;

typedef struct {
    const char* url;
    RouteHandler handler;
} Route;

char* escape(const char *input) {
    static char output[1024];
    strcpy(output, input);
    // Simple HTML escaping for demonstration
    size_t len = strlen(output);
    for (size_t i = 0; i < len; i++) {
        if (output[i] == '<') {
            memmove(&output[i + 4], &output[i + 1], len - i);
            strcpy(&output[i], "&lt;");
            len += 3;
            i += 3;
        } else if (output[i] == '>') {
            memmove(&output[i + 4], &output[i + 1], len - i);
            strcpy(&output[i], "&gt;");
            len += 3;
            i += 3;
        }
    }
    return output;
}

const char* hello(const char *username) {
    static char greeting[256];
    snprintf(greeting, sizeof(greeting), "Hello %s", escape(username));
    return greeting;
}

Route routes[] = {
    { "/hello", { .func = hello } },
};

void handle_request(const char* url, const char* username) {
    for (int i = 0; i < sizeof(routes)/sizeof(routes[0]); i++) {
        if (strcmp(url, routes[i].url) == 0) {
            printf("%s\n", routes[i].handler.func(username));
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    const char *username = "User123";
    handle_request("/hello", username);
    return 0;
}