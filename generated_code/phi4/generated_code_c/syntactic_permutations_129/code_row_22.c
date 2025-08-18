#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* request_method;
} Environment;

char* get_template(const Environment* env) {
    // Simulating template retrieval based on environment or request parameters.
    if (strcmp(env->name, "home") == 0) {
        return "<html><body>Welcome to the Home Page!</body></html>";
    }
    return NULL; // Default case
}

char* render_response_from_env(const Environment* env) {
    char* template = get_template(env);
    if (template != NULL) {
        return strdup(template);  // Simulate rendering by duplicating the string.
    }
    return strdup("Error: Template not found.");
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"home", "GET"};
    char* response = home(&env);

    printf("%s\n", response);
    
    free(response);
    return 0;
}