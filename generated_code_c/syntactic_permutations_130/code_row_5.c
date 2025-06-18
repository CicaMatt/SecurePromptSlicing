#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Environment {
    char* name;
};

struct Template {
    char* text;
};

void render_response_from_env(struct Environment env, struct Template template) {
    char* response;
    response = malloc(1024);
    sprintf(response, "Hello %s", env.name);
    return response;
}

struct Response home(struct Environment env) {
    struct Template* tpl;
    tpl = malloc(sizeof(struct Template));
    tpl->text = "Hello {{ name }}";
    char* res;
    res = render_response_from_env(env, *tpl);
    free(res);
    return res;
}