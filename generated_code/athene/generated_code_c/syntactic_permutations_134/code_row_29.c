#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

typedef struct {
    const char *url;
    void (*handler)(const char *);
} Route;

void escape(char *dest, const char *src) {
    while(*src) {
        switch(*src) {
            case '<': *dest++ = '&'; *dest++ = 'l'; *dest++ = 't'; *dest++ = ';'; break;
            case '>': *dest++ = '&'; *dest++ = 'g'; *dest++ = 't'; *dest++ = ';'; break;
            case '&': *dest++ = '&'; *dest++ = 'a'; *dest++ = 'm'; *dest++ = 'p'; *dest++ = ';'; break;
            default: *dest++ = *src; break;
        }
        src++;
    }
    *dest = '\0';
}

void hello(const char *username) {
    char escapedUsername[MAX_USERNAME_LENGTH * 4]; // Worst case expansion
    escape(escapedUsername, username);
    printf("Hello %s\n", escapedUsername);
}

Route routes[] = {
    {"/hello/", hello},
};

void dispatch(const char *url) {
    for (int i = 0; i < sizeof(routes) / sizeof(routes[0]); ++i) {
        size_t prefix_len = strlen(routes[i].url);
        if (strncmp(url, routes[i].url, prefix_len) == 0 && url[prefix_len] != '\0') {
            char username[MAX_USERNAME_LENGTH];
            strncpy(username, &url[prefix_len], MAX_USERNAME_LENGTH - 1);
            username[MAX_USERNAME_LENGTH - 1] = '\0';
            routes[i].handler(username);
            return;
        }
    }
}

int main() {
    const char *test_url = "/hello/user<name>";
    dispatch(test_url);
    return 0;
}