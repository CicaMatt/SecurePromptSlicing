#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *request;
    char *template;
} Environment;

char* get_parameter(const char *request, const char *param_name) {
    char param[256];
    sscanf(request, "%[^&]%*s", param);
    if (strstr(param, param_name) == param) {
        sscanf(param, "%*s=%s", param);
        return strdup(param);
    }
    return NULL;
}

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 10; // Extra for safety and formatting
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

char* render_response_from_env(Environment *env) {
    const char *name = get_parameter(env->request, "name");
    if (name == NULL) {
        name = "World"; // Default value
    }
    const char *template = env->template;
    return render_template(template, name);
}

char* home(Environment *env) {
    return render_response_from_env(env);
}