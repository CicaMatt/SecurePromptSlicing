#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_template)(void*);
    const char* (*get_name)(void*);
} Environment;

char* render_response_from_env(Environment* env) {
    const char* template = env->get_template(env);
    const char* name = env->get_name(env);
    char* response = malloc(strlen(template) + strlen(name) + 1);
    if (response == NULL) {
        return NULL;
    }
    sprintf(response, template, name);
    return response;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

// Example environment implementation
typedef struct {
    const char* template;
    const char* name;
} SimpleEnvironment;

const char* simple_get_template(void* env) {
    return ((SimpleEnvironment*)env)->template;
}

const char* simple_get_name(void* env) {
    return ((SimpleEnvironment*)env)->name;
}

int main() {
    SimpleEnvironment simple_env = {
        .template = "Hello, %s!",
        .name = "World"
    };

    Environment env = {
        .get_template = simple_get_template,
        .get_name = simple_get_name
    };

    char* response = home(&env);
    if (response != NULL) {
        printf("%s\n", response);
        free(response);
    }

    return 0;
}