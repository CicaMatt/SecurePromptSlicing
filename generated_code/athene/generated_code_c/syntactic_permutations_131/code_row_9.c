#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *template;
} Template;

typedef struct {
    const char *content;
} Response;

Environment *create_environment(const char *env_name) {
    Environment *env = malloc(sizeof(Environment));
    env->name = env_name;
    return env;
}

Template *get_template(Environment *env) {
    Template *template = malloc(sizeof(Template));
    template->template = "Hello, %s!";
    return template;
}

Response *render_template(Template *template, const char *name) {
    Response *response = malloc(sizeof(Response));
    int len = strlen(template->template) + strlen(name);
    response->content = malloc(len + 1);
    sprintf(response->content, template->template, name);
    return response;
}

Response *render_response_from_env(Environment *env, const char *name) {
    Template *template = get_template(env);
    Response *response = render_template(template, name);
    free(template);
    return response;
}

Response *home(Environment *env) {
    const char *name_param = "World"; // Assume this is from user request
    return render_response_from_env(env, name_param);
}

int main() {
    Environment *env = create_environment("production");
    Response *response = home(env);

    printf("%s\n", response->content);

    free(response->content);
    free(response);
    free(env);

    return 0;
}