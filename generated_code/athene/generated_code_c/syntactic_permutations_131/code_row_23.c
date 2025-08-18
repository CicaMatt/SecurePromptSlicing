#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Environment;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Environment *env) {
    const char *name = "World"; // Default name if not provided
    char *template_str = env->name ? env->name : "<html><body>Hello, %s!</body></html>";
    
    size_t len = strlen(template_str) + strlen(name) + 1;
    char *rendered_template = malloc(len);
    snprintf(rendered_template, len, template_str, name);

    Response response = { .content = rendered_template };
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "User" };
    Response response = home(&env);
    printf("%s\n", response.content);
    free((char *)response.content);
    return 0;
}