#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    Request *request;
    const char *template;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env) {
    char name[100];
    if (env->request->name != NULL) {
        strncpy(name, env->request->name, 99);
        name[99] = '\0';
    } else {
        strcpy(name, "World");
    }
    size_t template_len = strlen(env->template);
    char rendered_template[512];
    snprintf(rendered_template, sizeof(rendered_template), env->template, name);
    Response response = { .content = strdup(rendered_template) };
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}