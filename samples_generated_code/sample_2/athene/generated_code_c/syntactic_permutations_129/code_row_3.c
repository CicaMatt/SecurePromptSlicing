#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_parameter)(const char* key);
    const char* template;
} Environment;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Environment env) {
    const char* name = env.get_parameter("name");
    size_t len = strlen(env.template) + strlen(name) + 1;
    char* rendered_template = malloc(len);
    snprintf(rendered_template, len, env.template, name);
    Response response = { .content = rendered_template };
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}