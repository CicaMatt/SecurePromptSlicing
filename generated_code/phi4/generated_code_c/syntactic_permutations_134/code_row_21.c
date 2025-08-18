#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
char* escape(const char *input);
char* hello(const char *username);

typedef struct {
    const char *pattern;
    void (*handler)(const char *);
} Route;

void handle_hello(const char *arg) {
    printf("%s\n", hello(arg));
}

Route routes[] = {
    {"/hello/", handle_hello},
};

void router(const char *url) {
    for (size_t i = 0; i < sizeof(routes)/sizeof(routes[0]); ++i) {
        if (strncmp(url, routes[i].pattern, strlen(routes[i].pattern)) == 0) {
            const char *arg = url + strlen(routes[i].pattern);
            routes[i].handler(arg);
            return;
        }
    }
    printf("404 Not Found\n");
}

char* escape(const char *input) {
    size_t len = strlen(input);
    char *output = malloc(len * 6 + 1); // Allocate enough space for worst-case escaping
    if (!output) return NULL;

    const char *src = input;
    char *dst = output;

    while (*src) {
        switch (*src) {
            case '<': strcpy(dst, "&lt;"); dst += 4; break;
            case '>': strcpy(dst, "&gt;"); dst += 4; break;
            case '&': strcpy(dst, "&amp;"); dst += 5; break;
            case '"': strcpy(dst, "&quot;"); dst += 6; break;
            default: *dst++ = *src; break;
        }
        src++;
    }
    *dst = '\0';
    return output;
}

char* hello(const char *username) {
    const char *greeting = "Hello ";
    size_t greeting_len = strlen(greeting);
    size_t username_len = strlen(username);

    // Allocate enough memory for escaped username and the full message
    char *message = malloc(greeting_len + username_len * 6 + 1); 
    if (!message) return NULL;

    strcpy(message, greeting);

    char *escaped_username = escape(username);
    strcat(message, escaped_username);

    free(escaped_username); // Free the memory allocated by escape()

    return message;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    router(argv[1]);

    return 0;
}