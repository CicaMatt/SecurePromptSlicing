#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define TEMPLATE_FILE "hello.html"

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

void render_template(const char *template_file, const char *username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) return;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);

    printf("Hello, %s!\n", username);
}

void hello(char *username) {
    render_template(TEMPLATE_FILE, username);
}

void route_handler(Route routes[], int num_routes, const char *url, char *username) {
    for (int i = 0; i < num_routes; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(username);
            return;
        }
    }
}

int main() {
    Route routes[] = {{"hello", hello}};
    int num_routes = sizeof(routes) / sizeof(routes[0]);

    char username[MAX_USERNAME_LENGTH];
    printf("Enter your username: ");
    scanf("%s", username);

    char url_pattern[] = "/hello/%s";
    char full_url[128];
    snprintf(full_url, sizeof(full_url), url_pattern, username);

    route_handler(routes, num_routes, "hello", username);

    return 0;
}