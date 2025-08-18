#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*func)(const char*);
} Route;

typedef struct {
    Route routes[10];
    int count;
} Router;

Router router = { .count = 0 };

void add_route(const char* path, const char* (*func)(const char*)) {
    router.routes[router.count++] = (Route){.func = func};
}

const char* escape(const char* str) {
    static char buffer[1024];
    int len = strlen(str);
    int pos = 0;
    for (int i = 0; i < len; ++i) {
        switch (str[i]) {
            case '<': strcpy(buffer + pos, "&lt;"); pos += 4; break;
            case '>': strcpy(buffer + pos, "&gt;"); pos += 4; break;
            case '&': strcpy(buffer + pos, "&amp;"); pos += 5; break;
            case '"': strcpy(buffer + pos, "&quot;"); pos += 6; break;
            default: buffer[pos++] = str[i]; break;
        }
    }
    buffer[pos] = '\0';
    return buffer;
}

const char* hello(const char* username) {
    static char greeting[128];
    snprintf(greeting, sizeof(greeting), "Hello, %s!", escape(username));
    return greeting;
}

void handle_request(const char* path, const char* arg) {
    for (int i = 0; i < router.count; ++i) {
        if (strcmp(path, "/hello") == 0 && router.routes[i].func != NULL) {
            const char* response = router.routes[i].func(arg);
            printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", response);
            return;
        }
    }
    printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nPage not found");
}

int main() {
    add_route("/hello", hello);

    // Simulate a request to /hello/username
    handle_request("/hello", "username");

    return 0;
}