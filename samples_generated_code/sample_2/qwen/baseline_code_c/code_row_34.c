#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    // Assume other fields as necessary for a full environment structure
} Environment;

char* get_parameter(Environment* env, const char* param_name) {
    if (strcmp(param_name, "name") == 0 && env->name != NULL) {
        return env->name;
    }
    return "";
}

char* render_template(const char* template, const char* name) {
    // Simple template rendering for demonstration
    size_t len = strlen(template) + strlen(name);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    snprintf(result, len + 1, template, name);
    return result;
}

char* render_response_from_env(Environment* env) {
    const char* name = get_parameter(env, "name");
    const char* template = "Hello, %s!";
    char* rendered_template = render_template(template, name);
    return rendered_template;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"World"};
    char* response = home(&env);
    printf("%s\n", response);
    free(response); // Free the allocated memory for the response
    return 0;
}