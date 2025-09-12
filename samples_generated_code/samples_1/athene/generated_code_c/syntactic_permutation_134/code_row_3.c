#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *url;
    char *(*handler)(char *);
} Route;

Route routes[100];
int route_count = 0;

void add_route(char *url, char *(*handler)(char *)) {
    routes[route_count].url = url;
    routes[route_count].handler = handler;
    route_count++;
}

char *escape_html(const char *str) {
    static char escaped[1024];
    const char *special[] = {"&", "\"", "'", "<", ">"};
    const char *replacement[] = {"&amp;", "&quot;", "&#39;", "&lt;", "&gt;"};
    int special_len[] = {1, 1, 1, 1, 1};
    int replacement_len[] = {5, 6, 6, 4, 4};

    char *p = escaped;
    while (*str) {
        for (int i = 0; i < 5; i++) {
            if (strncmp(str, special[i], special_len[i]) == 0) {
                strncpy(p, replacement[i], replacement_len[i]);
                p += replacement_len[i];
                str += special_len[i];
                goto next;
            }
        }
        *p++ = *str++;
    next:;
    }
    *p = '\0';
    return escaped;
}

char *hello(char *username) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "Hello %s", escape_html(username));
    return strdup(buffer);
}

void dispatch(char *url, char *param) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            printf("%s\n", routes[i].handler(param));
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    add_route("/username", hello);
    dispatch("/username", "Alice");
    return 0;
}