#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*func)(const char*);
} Route;

typedef struct {
    const char* url;
    Route route;
} Mapping;

const char* escape(const char* input) {
    static char output[1024];
    strcpy(output, "");
    for (int i = 0; i < strlen(input); i++) {
        switch (input[i]) {
            case '<': strcat(output, "&lt;"); break;
            case '>': strcat(output, "&gt;"); break;
            case '&': strcat(output, "&amp;"); break;
            case '"': strcat(output, "&quot;"); break;
            default: strncat(output, input + i, 1); break;
        }
    }
    return output;
}

const char* hello(const char* username) {
    static char greeting[256];
    sprintf(greeting, "Hello %s", escape(username));
    return greeting;
}

void handle_request(const Mapping mappings[], int count, const char* url) {
    for (int i = 0; i < count; i++) {
        if (strcmp(mappings[i].url, url) == 0) {
            const char* username = url + strlen("/hello/");
            printf("%s\n", mappings[i].route.func(username));
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    Mapping mappings[] = { { "/hello/", { hello } } };
    int count = sizeof(mappings) / sizeof(mappings[0]);

    // Simulate a request
    const char* url = "/hello/user123";
    handle_request(mappings, count, url);

    return 0;
}