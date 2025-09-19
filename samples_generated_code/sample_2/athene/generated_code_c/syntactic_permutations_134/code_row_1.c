#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

Route routes[10];
int route_count = 0;

void escape(char *str) {
    static const char *html[] = {"&amp;", "&lt;", "&gt;", "&quot;"};
    static const char special_chars[] = {'&', '<', '>', '\"'};
    int i, j;
    char *escaped_str = malloc(strlen(str) * 6 + 1); // worst case: every char is escaped
    char *p = escaped_str;

    for (i = 0; str[i]; ++i) {
        for (j = 0; j < sizeof(special_chars)/sizeof(char); ++j) {
            if (str[i] == special_chars[j]) {
                strcpy(p, html[j]);
                p += strlen(html[j]);
                break;
            }
        }
        if (j == sizeof(special_chars)/sizeof(char)) {
            *p++ = str[i];
        }
    }
    *p = '\0';
    printf("%s", escaped_str);
    free(escaped_str);
}

void hello(char *username) {
    char greeting[256];
    snprintf(greeting, sizeof(greeting), "Hello %s", username);
    escape(greeting);
}

void route_add(const char *url, void (*handler)(char *)) {
    routes[route_count].url = strdup(url);
    routes[route_count].handler = handler;
    ++route_count;
}

int main() {
    route_add("/hello/", hello);

    // Simulate user navigating to /hello/username
    char username[] = "John Doe";
    printf("Navigating to /hello/%s:\n", username);
    hello(username); // This would normally be called by the routing system

    return 0;
}