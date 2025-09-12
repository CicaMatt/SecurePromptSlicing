#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Environment;

char* get_template(Environment *env) {
    // Placeholder for actual template fetching logic
    return "Hello, %s!";
}

char* render_response_from_env(Environment *env) {
    char* user_name = env->name ? env->name : "Guest";
    char* template = get_template(env);
    
    size_t response_size = strlen(template) + strlen(user_name) + 1;
    char* response = malloc(response_size);
    
    if (response == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    snprintf(response, response_size, template, user_name);
    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = strdup("Alice");  // Example name

    char* response = home(&env);
    
    printf("%s\n", response);
    
    free(response);
    free(env.name);
    
    return 0;
}