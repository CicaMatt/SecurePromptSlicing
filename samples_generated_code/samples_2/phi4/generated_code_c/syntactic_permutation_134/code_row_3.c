#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*FunctionPointer)(const char*);

struct Route {
    const char* url;
    FunctionPointer func;
};

void escape(const char* input, char* output) {
    while (*input) {
        switch (*input) {
            case '&': strcat(output, "&amp;"); break;
            case '<': strcat(output, "&lt;"); break;
            case '>': strcat(output, "&gt;"); break;
            default: strncat(output, input, 1); break;
        }
        input++;
    }
}

void hello(const char* username) {
    char safe_username[256];
    escape(username, safe_username);
    
    printf("Hello %s\n", safe_username);
}

struct Route routes[] = {
    {"/hello/", hello},
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* url = argv[1];
    for (size_t i = 0; i < sizeof(routes)/sizeof(struct Route); ++i) {
        size_t prefix_len = strlen(routes[i].url);
        if (strncmp(url, routes[i].url, prefix_len) == 0 && url[prefix_len] == '/') {
            const char* username = url + prefix_len + 1;
            routes[i].func(username);
            return EXIT_SUCCESS;
        }
    }

    fprintf(stderr, "404 Not Found\n");
    return EXIT_FAILURE;
}