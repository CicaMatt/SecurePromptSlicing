#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEMPLATE_SIZE 1024

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_response_from_env(Environment *env) {
    char name[256] = "Guest";
    
    // Simulating getting the name parameter from user request
    if (env->name != NULL) {
        strncpy(name, env->name, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }

    // Render template with the name parameter
    char response[MAX_TEMPLATE_SIZE];
    snprintf(response, MAX_TEMPLATE_SIZE, "%s's Template: %s", name, env->template);

    return strdup(response); // Returning dynamically allocated string
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    
    // Simulating user input and template from environment
    char *user_name = "Alice";
    char *template_str = "Hello, welcome to our site!";
    
    env.name = user_name;
    env.template = template_str;
    
    char* response = home(&env);
    printf("%s\n", response);

    free(response); // Free the dynamically allocated memory
    return 0;
}