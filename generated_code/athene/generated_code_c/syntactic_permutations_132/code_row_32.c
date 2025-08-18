#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

Route routes[100];
int route_count = 0;

void add_route(const char *url, void (*handler)(char *)) {
    if (route_count < 100) {
        routes[route_count].url = strdup(url);
        routes[route_count].handler = handler;
        route_count++;
    }
}

void render_template(const char *template_file, const char *username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) {
        perror("Failed to open template file");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t pos = 0;
        while ((pos = strstr(buffer + pos, "{{username}}")) != NULL) {
            memmove(pos + strlen(username), pos + strlen("{{username}}"), strlen(pos + strlen("{{username}}")) - strlen("{{username}}") + 1);
            memcpy(pos, username, strlen(username));
        }
        printf("%s", buffer);
    }

    fclose(file);
}

void hello(char *username) {
    render_template("hello.html", username);
}

char *extract_username(const char *url) {
    const char *start = strrchr(url, '/');
    if (start == NULL || start[1] == '\0') return NULL;
    return strdup(start + 1);
}

void dispatch_request(const char *request_url) {
    for (int i = 0; i < route_count; ++i) {
        if (strcmp(routes[i].url, request_url) == 0) {
            char *username = extract_username(request_url);
            if (username != NULL) {
                routes[i].handler(username);
                free(username);
            }
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    add_route("/hello/", hello);
    dispatch_request("/hello/JohnDoe"); // Example request
    return 0;
}