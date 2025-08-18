#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100
#define TEMPLATE_FILE "hello.html"

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

void render_template(const char *template_file, const char *username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) {
        printf("Template file not found.\n");
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t pos;
        while ((pos = strstr(buffer, "{{username}}") - buffer) != -1) {
            memmove(buffer + pos + strlen(username), buffer + pos + 9, strlen(buffer) - pos - 8);
            strncpy(buffer + pos, username, strlen(username));
        }
        printf("%s", buffer);
    }
    fclose(file);
}

void hello(char *username) {
    render_template(TEMPLATE_FILE, username);
}

void route_handler(Route *route, const char *url) {
    if (strncmp(route->url, url, strlen(url)) == 0 && *(url + strlen(route->url)) == '/') {
        char username[MAX_USERNAME_LEN];
        sscanf(url + strlen(route->url), "%s", username);
        route->handler(username);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    Route routes[] = {{"hello", hello}};
    const int num_routes = sizeof(routes) / sizeof(routes[0]);

    char user_input_url[256];
    while (1) {
        printf("Enter URL: ");
        scanf("%s", user_input_url);
        for (int i = 0; i < num_routes; i++) {
            route_handler(&routes[i], user_input_url);
            break;
        }
    }

    return 0;
}