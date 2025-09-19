#include <stdio.h>
#include <string.h>

typedef struct {
    const char* request;
    const char* template;
} Env;

char* get_param(const char* request, const char* key) {
    char param[1024];
    sscanf(request, "%*[^&]%[^&]", param);
    if (strstr(param, key)) {
        sscanf(param, "%*[^=]=%s", param);
        return strdup(param);
    }
    return NULL;
}

char* render_template(const char* template, const char* name) {
    int len = strlen(template) + strlen(name) + 10;
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

const char* render_response_from_env(Env env) {
    const char* name = get_param(env.request, "name");
    if (name == NULL) {
        name = "World";
    }
    const char* template = env.template;
    char *response = render_template(template, name);
    return response;
}

const char* home(Env env) {
    return render_response_from_env(env);
}