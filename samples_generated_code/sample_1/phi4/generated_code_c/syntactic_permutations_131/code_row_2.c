#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_response_from_env(Environment *env) {
    char name[256];
    if (env->name != NULL) {
        strncpy(name, env->name, sizeof(name));
    } else {
        snprintf(name, sizeof(name), "Guest");
    }
    
    char *response = malloc(strlen(env->template) + strlen(name) + 1);
    if (response == NULL) {
        return NULL;
    }

    sprintf(response, env->template, name);
    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"John Doe", "Hello, %s! Welcome to our site."};
    
    char *response = home(&env);
    if (response != NULL) {
        printf("%s\n", response);
        free(response);
    } else {
        fprintf(stderr, "Failed to render response.\n");
    }

    return 0;
}