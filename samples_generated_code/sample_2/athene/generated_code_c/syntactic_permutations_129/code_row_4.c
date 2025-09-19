#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *template_content;
} Template;

typedef struct {
    const char *content_type;
    const char *body;
} Response;

Environment *create_environment(const char *name) {
    Environment *env = malloc(sizeof(Environment));
    env->name = name;
    return env;
}

Template *get_template_from_env(Environment *env) {
    Template *template = malloc(sizeof(Template));
    template->template_content = "Hello, %s!";
    return template;
}

Response *render_response_from_env(Environment *env) {
    const char *name = env->name;
    Template *template = get_template_from_env(env);
    
    size_t body_len = strlen(template->template_content) + strlen(name) + 1;
    char *body = malloc(body_len);
    snprintf(body, body_len, template->template_content, name);

    Response *response = malloc(sizeof(Response));
    response->content_type = "text/html";
    response->body = body;

    free(template);
    return response;
}

Response *home(const char *name) {
    Environment *env = create_environment(name);
    Response *response = render_response_from_env(env);
    free(env);
    return response;
}