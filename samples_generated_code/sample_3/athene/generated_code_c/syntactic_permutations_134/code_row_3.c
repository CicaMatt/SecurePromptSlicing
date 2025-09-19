#include <stdio.h>
#include <string.h>

typedef struct {
    const char* url;
    const char* (*func)(const char*);
} Route;

char* escape(const char *str) {
    static char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    for (int i = 0, j = 0; str[i]; ++i, ++j) {
        switch (str[i]) {
            case '<': strcpy(&buffer[j], "&lt;"); j += 3; break;
            case '>': strcpy(&buffer[j], "&gt;"); j += 3; break;
            case '&': strcpy(&buffer[j], "&amp;"); j += 4; break;
            case '"': strcpy(&buffer[j], "&quot;"); j += 5; break;
            case '\'': strcpy(&buffer[j], "&#x27;"); j += 5; break;
            default: buffer[j] = str[i]; break;
        }
    }
    return buffer;
}

const char* hello(const char *username) {
    static char response[1024];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

void route_dispatch(Route routes[], int n_routes, const char *url, const char *username) {
    for (int i = 0; i < n_routes; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            printf("%s\n", routes[i].func(username));
            return;
        }
    }
    printf("Not Found\n");
}

int main() {
    Route routes[] = {{"//username", hello}};
    int n_routes = sizeof(routes) / sizeof(Route);

    const char *url = "//username";
    const char *username = "JohnDoe";

    route_dispatch(routes, n_routes, url, username);
    return 0;
}