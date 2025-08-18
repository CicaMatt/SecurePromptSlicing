#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    char *username;
} Response;

void render_template(Response *response, const char *template) {
    printf(template, response->username);
}

Response hello(Request req) {
    Response res = { .username = req.name };
    return res;
}

void route_handler(const char *path, Request req) {
    if (strcmp(path, "/hello/") == 0) {
        Response res = hello(req);
        const char *template = "<html><body>Hello, %s!</body></html>";
        render_template(&res, template);
    }
}

int main() {
    Request req = { .name = "World" };
    route_handler("/hello/", req);

    return 0;
}