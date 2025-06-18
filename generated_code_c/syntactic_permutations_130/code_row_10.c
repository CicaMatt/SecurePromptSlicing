#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define MAX_ENV 100

struct env {
    char *name;
    void *value;
};

struct request {
    struct env *env;
    int env_len;
};

struct response {
    int status_code;
    char *template;
    void *data;
};

char *render(const char *template, const struct env *env) {
    // Implement a simple templating engine here.
    return strdup("Rendered template");
}

struct response render_response_from_env(const struct request *req) {
    char *template = (char *) req->env[0].value;
    struct env new_env = {.name="rendered", .value=render(template, req->env)};
    return (struct response){
        .status_code = 200,
        .template = template,
        .data = &new_env
    };
}

struct response home(const struct request *req) {
    struct response res = render_response_from_env(req);
    return (struct response){
        .status_code = 200,
        .template = "home.html",
        .data = &res
    };
}