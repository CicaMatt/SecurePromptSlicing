#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(const char*);
} Environment;

char* get_example_template(const char* name) {
    if (strcmp(name, "example") == 0) {
        return "<html><body>Hello, %s!</body></html>";
    }
    return NULL;
}

Environment create_environment() {
    Environment env;
    env.get_template = get_example_template;
    return env;
}

char* render_response_from_env(Environment* env, const char* name) {
    char* template = env->get_template(name);
    if (template != NULL) {
        char* response = malloc(256); // Allocate memory for the response
        snprintf(response, 256, template, "World");
        return response;
    }
    return NULL;
}

char* home(Environment* env) {
    return render_response_from_env(env, "example");
}

int main() {
    Environment env = create_environment();
    char* response = home(&env);
    if (response != NULL) {
        printf("%s\n", response);
        free(response); // Free the allocated memory for the response
    }
    return 0;
}