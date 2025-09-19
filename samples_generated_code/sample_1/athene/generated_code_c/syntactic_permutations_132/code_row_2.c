#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

typedef struct {
    char *username;
} RequestContext;

void render_template(char *template_file, char *username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) {
        perror("Failed to open template file");
        exit(1);
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf(buffer);
    }
    fclose(file);
    printf("<p>Username: %s</p>\n", username);
}

void user_page_handler(char *username) {
    render_template("user.html", username);
}

void route_request(Route routes[], int num_routes, char *url) {
    for (int i = 0; i < num_routes; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            RequestContext context;
            sscanf(url, "/%s", context.username);
            routes[i].handler(context.username);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    Route routes[] = {{"/<username>", user_page_handler}};
    int num_routes = sizeof(routes) / sizeof(Route);

    char *url = "/john_doe"; // Example URL
    route_request(routes, num_routes, url);

    return 0;
}