#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Environment;

typedef struct {
    const char* content_type;
    const char* body;
} Response;

const char* get_parameter(const Environment *env, const char *param_name) {
    if (strcmp(param_name, "name") == 0 && env->name != NULL) {
        return env->name;
    }
    return "";
}

char* render_template(const char *template_str, const char *name) {
    size_t len = strlen(template_str) + strlen(name) + 1;
    char *result = malloc(len);
    snprintf(result, len, template_str, name);
    return result;
}

Response render_response_from_env(Environment *env) {
    const char* name = get_parameter(env, "name");
    const char* template = "Hello, %s!";
    char* rendered_template = render_template(template, name);

    Response response = {
        .content_type = "text/html",
        .body = rendered_template
    };

    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World" };
    Response response = home(&env);

    printf("Content-Type: %s\n", response.content_type);
    printf("%s\n", response.body);

    free((void*)response.body); // Free the allocated memory for the rendered template
    return 0;
}