#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

typedef struct {
    const char *template;
    char *rendered;
} Template;

void render_template(Template *tmpl, const char *username) {
    int tmpl_len = strlen(tmpl->template);
    int username_len = strlen(username);
    int rendered_len = tmpl_len + username_len + 1; // +1 for null terminator
    tmpl->rendered = malloc(rendered_len);
    strcpy(tmpl->rendered, tmpl->template);
    char *pos = strstr(tmpl->rendered, "{{username}}");
    if (pos) {
        memmove(pos + username_len, pos + 12, rendered_len - (pos - tmpl->rendered) - 12); // 12 for {{username}}
        memcpy(pos, username, username_len);
    }
}

void hello(char *username) {
    Template tmpl = { .template = "<html><body>Hello, {{username}}!</body></html>" };
    render_template(&tmpl, username);
    printf("%s\n", tmpl->rendered);
    free(tmpl.rendered);
}

void route_handler(Route *route, const char *url, const char *username) {
    if (strcmp(route->url, url) == 0) {
        route->handler((char *)username);
    }
}

int main() {
    Route routes[] = { { "/hello/", hello } };
    const size_t num_routes = sizeof(routes) / sizeof(routes[0]);

    char *url = "/hello/";
    char *username = "World";

    for (size_t i = 0; i < num_routes; ++i) {
        route_handler(&routes[i], url, username);
    }

    return 0;
}