#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated environment structure
typedef struct {
    char **variables;
    size_t variables_count;
} Environment;

// Simulated template rendering function
char* render_template(const char *template, const char *name) {
    // For simplicity, we just replace a placeholder in the template with the name.
    char *result = malloc(strlen(template) + strlen(name) + 1);
    if (!result) return NULL;
    
    const char *placeholder = "{name}";
    char *pos = strstr(template, placeholder);
    if (pos) {
        strncpy(result, template, pos - template);
        strcpy(result + (pos - template), name);
        strcpy(result + (pos - template) + strlen(name), pos + strlen(placeholder));
    } else {
        strcpy(result, template);
    }
    
    return result;
}

// Function to get a variable from the environment
const char* get_env_variable(Environment *env, const char *var_name) {
    for (size_t i = 0; i < env->variables_count; ++i) {
        if (strncmp(env->variables[i], var_name, strlen(var_name)) == 0 && 
            env->variables[i][strlen(var_name)] == '=') {
            return env->variables[i] + strlen(var_name) + 1;
        }
    }
    return NULL;
}

// Function to render response from environment
char* render_response_from_env(Environment *env) {
    const char *name = get_env_variable(env, "REQUEST_METHOD");
    if (!name) return "Error: 'name' parameter not found in request.";

    const char *template_str = get_env_variable(env, "TEMPLATE");
    if (!template_str) return "Error: Template not found in environment.";

    char *response = render_template(template_str, name);
    if (!response) return "Error: Failed to render template.";
    
    return response;
}

// Home function
char* home(Environment *env) {
    char *response = render_response_from_env(env);
    return response;
}

int main() {
    // Simulate environment setup
    const char *variables[] = {
        "REQUEST_METHOD=GET",
        "TEMPLATE=Hello, {name}!"
    };
    
    Environment env = { variables, 2 };

    // Call home function and print response
    char *response = home(&env);
    printf("%s\n", response);

    free(response);  // Free the allocated memory for the response
    return 0;
}