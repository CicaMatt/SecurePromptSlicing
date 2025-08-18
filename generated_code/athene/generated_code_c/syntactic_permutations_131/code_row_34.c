#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

char* get_param(Request *request, const char *param_name) {
    if (strcmp(param_name, "name") == 0) {
        return strdup(request->name);
    }
    return NULL;
}

const char* get_template(Environment *env) {
    return env->template;
}

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 2; // Extra for space and null terminator
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

char* render_response_from_env(Environment *env, Request *request) {
    const char *name = get_param(request, "name");
    if (name == NULL) {
        name = "World"; // Default value
    }
    const char *template = get_template(env);
    return render_template(template, name);
}

char* home(Environment *env, Request *request) {
    return render_response_from_env(env, request);
}

int main() {
    Environment env = {"Hello, %s!"};
    Request request = {"Alice"};
    char *response = home(&env, &request);
    printf("%s\n", response);
    free(response); // Free the allocated memory
    return 0;
}