#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_name(const Environment *env) {
    return env->name;
}

char* get_template(const Environment *env) {
    return env->template;
}

char* render_response_from_env(Environment *env) {
    const char *name = get_name(env);
    const char *template = get_template(env);

    size_t buffer_size = strlen(template) + strlen(name) + 1;
    char *response = malloc(buffer_size);
    
    if (response == NULL) {
        return NULL; // Handle memory allocation failure
    }

    snprintf(response, buffer_size, template, name);
    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    char name[] = "John Doe";
    char template[] = "Hello, %s! Welcome to our website.";

    Environment env = {name, template};

    char *response = home(&env);

    if (response != NULL) {
        printf("%s\n", response);
        free(response);
    } else {
        fprintf(stderr, "Failed to render response.\n");
    }

    return 0;
}