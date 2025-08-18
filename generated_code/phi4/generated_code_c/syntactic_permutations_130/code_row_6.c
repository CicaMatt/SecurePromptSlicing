#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated environment and request structure
typedef struct {
    char *name;
} Request;

typedef struct {
    const char *template;
    void (*get_template)(const char **);
} Environment;

// Function declarations
char* render_response_from_env(Environment env, Request req);

void get_home_template(const char **template) {
    *template = "Hello, %s! Welcome to the home page.";
}

char* render_response_from_env(Environment env, Request req) {
    const char *template;
    env.get_template(&template);
    
    // Ensure the template and name are valid
    if (req.name == NULL || template == NULL) {
        return strdup("Invalid request or environment.");
    }

    size_t buffer_size = strlen(template) + strlen(req.name) + 1;
    char *response_buffer = malloc(buffer_size);

    snprintf(response_buffer, buffer_size, template, req.name);
    
    return response_buffer;
}

char* home(Environment env) {
    Request req = { .name = "User" };
    return render_response_from_env(env, req);
}

int main() {
    Environment env = { .template = NULL, .get_template = get_home_template };

    char *response = home(env);

    printf("%s\n", response);

    free(response);

    return 0;
}