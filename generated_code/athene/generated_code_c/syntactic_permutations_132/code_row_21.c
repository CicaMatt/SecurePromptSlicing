#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
} RequestContext;

void render_template(const char *template_name, const char *username) {
    printf("<html><body>");
    if (strcmp(template_name, "hello.html") == 0) {
        printf("Hello, %s!", username);
    }
    printf("</body></html>\n");
}

typedef void (*Handler)(RequestContext *);

void hello(RequestContext *context) {
    render_template("hello.html", context->username);
}

typedef struct {
    const char *url;
    Handler handler;
} Route;

Route routes[] = {
    {"/hello/<username>", hello},
};

int main() {
    // Simulate a request to /hello/John
    RequestContext req = {"John"};
    for (size_t i = 0; i < sizeof(routes) / sizeof(routes[0]); ++i) {
        if (routes[i].url != NULL && routes[i].handler != NULL) {
            char *username_start = strstr(routes[i].url, "<username>");
            if (username_start != NULL) {
                // Simulate URL matching and username extraction
                routes[i].handler(&req);
                break;
            }
        }
    }
    return 0;
}