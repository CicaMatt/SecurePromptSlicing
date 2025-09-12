#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *request_method;
    char *url_path;
    char *query_string;
} Request;

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_template(const char *template) {
    // Simple mockup rendering, in real scenarios this would be more complex
    size_t len = strlen(template);
    char *rendered = malloc(len + 1);
    if (!rendered) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(rendered, template);
    return rendered;
}

char* render_response_from_env(Environment env) {
    const char *name_param = getenv("NAME"); // Assuming environment variables are used for parameters

    if (!name_param) {
        name_param = "Guest";
    }

    char response[256];
    snprintf(response, sizeof(response), "%s: %s", env.name, render_template(env.template));
    
    return strdup(response);
}

char* home(Environment *env) {
    return render_response_from_env(*env);
}

int main() {
    Environment env;
    env.name = "Home Page";
    env.template = "<h1>Welcome, NAME!</h1>";

    char *response = home(&env);

    printf("%s\n", response);

    free(response);
    return 0;
}