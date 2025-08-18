#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *url;
    void (*handler)(const char *username);
} Route;

#define MAX_ROUTES 10
Route routes[MAX_ROUTES];
int route_count = 0;

void add_route(const char *url, void (*handler)(const char *username)) {
    if (route_count < MAX_ROUTES) {
        routes[route_count].url = url;
        routes[route_count].handler = handler;
        route_count++;
    }
}

char *escape(const char *str) {
    static char buffer[1024];
    const char *special_chars = "&<>'\"";
    const char *replacements[] = {"&amp;", "&lt;", "&gt;", "&#39;", "&quot;"};
    int j = 0;
    for (int i = 0; str[i]; i++) {
        int found = 0;
        for (int k = 0; special_chars[k]; k++) {
            if (str[i] == special_chars[k]) {
                strcpy(buffer + j, replacements[k]);
                j += strlen(replacements[k]);
                found = 1;
                break;
            }
        }
        if (!found) {
            buffer[j++] = str[i];
        }
    }
    buffer[j] = '\0';
    return buffer;
}

void hello(const char *username) {
    printf("Hello %s\n", escape(username));
}

int main() {
    add_route("/<username>", hello);

    // Simulate a user navigating to the URL
    const char *url = "/john";
    const char *username = url + 1; // Simplified for demonstration

    for (int i = 0; i < route_count; i++) {
        if (strstr(url, routes[i].url) == url) {
            routes[i].handler(username);
            break;
        }
    }

    return 0;
}