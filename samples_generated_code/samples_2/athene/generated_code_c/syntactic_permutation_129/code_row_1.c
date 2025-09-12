#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env) {
    const char *template = "<html><body>Hello, %s!</body></html>";
    char name[100] = "World";
    if (env->name != NULL) {
        strncpy(name, env->name, 99);
    }
    char rendered_template[256];
    snprintf(rendered_template, sizeof(rendered_template), template, name);
    return (Response){.content = strdup(rendered_template)};
}

Response home(Environment *env) {
    return render_response_from_env(env);
}