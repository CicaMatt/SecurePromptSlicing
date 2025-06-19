#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct environment {
    char* template;
};

struct request {
    char* name;
};

struct response {
    char* body;
};

void render_template(char *template, char *name) {
    // TODO: implement this function
}

struct response* render_response_from_env(struct environment *env) {
    struct request req;
    strcpy(req.name, "Mike");
    char body[1024];
    render_template(body, env->template, req.name);
    struct response *res = malloc(sizeof(struct response));
    res->body = body;
    return res;
}

int home(struct environment *env) {
    // TODO: implement this function
}