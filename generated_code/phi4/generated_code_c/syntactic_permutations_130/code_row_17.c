#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **variables;
} Environment;

typedef struct {
    const char *name;
} Request;

typedef struct {
    char *content;
} Response;

Response render_template_with_name(Environment *env, const char *template, const char *name) {
    Response response;
    char buffer[256];
    
    snprintf(buffer, sizeof(buffer), "%s says: %s", template, name);
    response.content = strdup(buffer); // Allocate memory for the content
    return response;
}

Response render_response_from_env(Environment *env, Request *request) {
    const char *name_param = "Guest"; // Default value if not found in env
    
    // Simulating retrieving 'name' from environment
    for (int i = 0; env->variables[i] != NULL; i++) {
        if (strncmp(env->variables[i], "name=", 5) == 0) {
            name_param = &env->variables[i][5];
            break;
        }
    }

    // Simulating template rendering
    const char *template = "Hello";
    Response response = render_template_with_name(env, template, name_param);
    return response;
}

Response home(Environment *env) {
    Request request = { .name = "SampleRequest" };
    return render_response_from_env(env, &request);
}

int main() {
    Environment env;
    char *variables[] = {"name=John", NULL}; // Example variables
    env.variables = variables;

    Response response = home(&env);

    printf("%s\n", response.content);
    
    free(response.content); // Free allocated memory for the content

    return 0;
}