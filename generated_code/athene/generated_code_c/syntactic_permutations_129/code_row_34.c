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
    const char *name = "World"; // Default value for name
    if (env != NULL && env->name != NULL) {
        name = env->name;
    }
    
    size_t len = strlen(name) + 30; // Estimate length for template rendering
    char *rendered_template = malloc(len);
    snprintf(rendered_template, len, "Hello, %s! Welcome to the service.", name);

    Response response = { .content = rendered_template };
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "User" };
    Response resp = home(&env);
    
    printf("%s\n", resp.content);
    free((void *)resp.content); // Free allocated memory
    return 0;
}