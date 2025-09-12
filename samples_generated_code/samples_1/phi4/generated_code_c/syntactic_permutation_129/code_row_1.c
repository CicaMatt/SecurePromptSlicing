#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEMPLATE_LENGTH 1024

typedef struct {
    char *template;
} Environment;

char* get_template_from_env(Environment *env) {
    return env->template;
}

char* render_response_from_env(Environment *env, const char *name_param) {
    char template[MAX_TEMPLATE_LENGTH];
    
    // Get the template from the environment
    strcpy(template, get_template_from_env(env));
    
    // Render the template with the name parameter
    char rendered[MAX_TEMPLATE_LENGTH];
    snprintf(rendered, sizeof(rendered), template, name_param);
    
    return strdup(rendered); // Return a dynamically allocated string
}

char* home(Environment *env) {
    const char *name = "John Doe"; // Example name parameter
    
    // Call render_response_from_env with the environment and name parameter
    char *response = render_response_from_env(env, name);
    
    return response; // Return the rendered response
}

int main() {
    Environment env;
    env.template = "<html><body>Hello, %s!</body></html>";
    
    char *response = home(&env);
    printf("%s\n", response);
    
    free(response); // Free dynamically allocated memory
    
    return 0;
}