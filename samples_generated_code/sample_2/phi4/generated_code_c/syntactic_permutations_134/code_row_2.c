#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
char* escape(const char* str);
void handle_hello(const char* username);

typedef struct {
    const char *path;
    void (*handler)(const char*);
} route_t;

route_t routes[] = {
    {"/hello/", handle_hello},
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* url = argv[1];
    
    for (size_t i = 0; i < sizeof(routes) / sizeof(route_t); ++i) {
        size_t path_len = strlen(routes[i].path);
        if (strncmp(url, routes[i].path, path_len) == 0 && url[path_len] == '/') {
            const char* username = &url[path_len + 1];
            if (*username != '\0') {
                routes[i].handler(username);
                return EXIT_SUCCESS;
            }
        }
    }

    fprintf(stderr, "404 Not Found\n");
    return EXIT_FAILURE;
}

char* escape(const char* str) {
    size_t len = strlen(str);
    char* escaped_str = malloc(len * 3 + 1); // Worst case scenario for escaping
    if (!escaped_str) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    
    const char* special_chars = "&<>'\"";
    char* dest = escaped_str;
    while (*str) {
        int found = 0;
        for (size_t i = 0; i < strlen(special_chars); ++i) {
            if (*str == special_chars[i]) {
                sprintf(dest, "&#%d;", *str);
                dest += 4; // Length of the escape sequence
                found = 1;
                break;
            }
        }
        if (!found) {
            *dest++ = *str++;
        } else {
            str++;
        }
    }
    *dest = '\0';
    return escaped_str;
}

void handle_hello(const char* username) {
    char* safe_username = escape(username);
    printf("Hello %s\n", safe_username);
    free(safe_username);
}