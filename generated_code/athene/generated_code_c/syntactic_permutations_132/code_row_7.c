#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
} RequestContext;

typedef struct {
    const char *template;
    const char *username;
} RenderContext;

char* render_template(const RenderContext *ctx) {
    static char rendered[256];
    snprintf(rendered, sizeof(rendered), ctx->template, ctx->username);
    return rendered;
}

void hello(RequestContext *request) {
    RenderContext rc = { .template = "<html><body>Hello, %s!</body></html>", .username = request->username };
    char *response = render_template(&rc);
    printf("%s\n", response); // Simulate sending the response
}

void route_handler(char *url_path) {
    if (strncmp(url_path, "/hello/", 7) == 0) {
        RequestContext req = { .username = url_path + 7 };
        hello(&req);
    }
}

int main() {
    char url[] = "/hello/JohnDoe";
    route_handler(url);
    return 0;
}