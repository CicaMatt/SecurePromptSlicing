#include <stdio.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *template;
} Response;

Response render_response_from_env(Environment *env) {
    const char *name = env->name;
    char template[256];
    snprintf(template, sizeof(template), "Hello, %s!", name);
    return (Response){.template = template};
}

const char* home(Environment *env) {
    Response response = render_response_from_env(env);
    return response.template;
}