#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    const char *value;
} EnvVar;

typedef struct {
    EnvVar *vars;
    size_t count;
} Environment;

typedef struct {
    const char *template;
    const char *name;
} TemplateResponse;

TemplateResponse render_template(const char *template, const char *name) {
    return (TemplateResponse){.template = template, .name = name};
}

const char *get_env_var(Environment env, const char *key) {
    for (size_t i = 0; i < env.count; ++i) {
        if (strcmp(env.vars[i].key, key) == 0) {
            return env.vars[i].value;
        }
    }
    return NULL;
}

char *render_response_from_env(Environment env) {
    const char *name = get_env_var(env, "name");
    const char *template = "<html><body>Hello, %s!</body></html>";
    TemplateResponse response = render_template(template, name);
    size_t len = strlen(response.template) + strlen(name) + 1;
    char *rendered_response = malloc(len);
    snprintf(rendered_response, len, response.template, name);
    return rendered_response;
}

char *home(Environment env) {
    return render_response_from_env(env);
}