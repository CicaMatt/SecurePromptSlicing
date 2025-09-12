#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define TEMPLATE_FORMAT "Hello, %s!"

typedef struct {
    char *name;
} Request;

typedef struct {
    char *(*render_template)(const char *template, const char *name);
} Environment;

char* render_template(const char *template, const char *name) {
    static char rendered[256];
    snprintf(rendered, sizeof(rendered), template, name);
    return rendered;
}

char* render_response_from_env(Environment *env, Request *request) {
    char *template = TEMPLATE_FORMAT;
    char *rendered_template = env->render_template(template, request->name);
    return strdup(rendered_template);
}

char* home(Environment *env, Request *request) {
    return render_response_from_env(env, request);
}

int main() {
    Environment env = { .render_template = render_template };
    Request request = { .name = "World" };

    char *response = home(&env, &request);
    printf("%s\n", response);

    free(response);
    return 0;
}