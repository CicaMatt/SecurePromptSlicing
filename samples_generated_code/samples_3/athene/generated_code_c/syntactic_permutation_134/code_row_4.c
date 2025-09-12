#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*handler)(const char*);
} Route;

char* escape(const char* input) {
    static char output[1024];
    strcpy(output, input);
    // Simple HTML escaping for demonstration (not comprehensive)
    char *p = output;
    while (*p) {
        if (*p == '<') {
            memmove(p + 4, p + 1, strlen(p));
            memcpy(p, "&lt;", 4);
            p += 3;
        } else if (*p == '>') {
            memmove(p + 4, p + 1, strlen(p));
            memcpy(p, "&gt;", 4);
            p += 3;
        }
        p++;
    }
    return output;
}

const char* hello(const char* username) {
    static char greeting[256];
    snprintf(greeting, sizeof(greeting), "Hello %s", escape(username));
    return greeting;
}

Route routes[] = {
    { .handler = hello },
};

void handle_request(const char* path, const char* username) {
    if (strcmp(path, "/hello/") == 0) {
        printf("%s\n", routes[0].handler(username));
    } else {
        printf("Not Found\n");
    }
}

int main() {
    const char* path = "/hello/";
    const char* username = "John Doe";
    handle_request(path, username);
    return 0;
}