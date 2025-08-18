#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_name_param(Environment *env) {
    return env->name;
}

char* get_template(Environment *env) {
    return env->template;
}

char* render_template(const char *template, const char *name) {
    size_t template_len = strlen(template);
    size_t name_len = strlen(name);

    // Create a buffer to hold the rendered content
    char *rendered = malloc(template_len + name_len + 1); 
    if (rendered == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Render the template with the name parameter
    snprintf(rendered, template_len + name_len + 1, "%s%s", template, name);

    return rendered;
}

char* render_response_from_env(Environment *env) {
    const char *name_param = get_name_param(env);
    const char *template_str = get_template(env);

    // Render the response
    char *rendered_content = render_template(template_str, name_param);

    return rendered_content;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = "Alice";
    env.template = "<html><body>Hello, ";

    char *response = home(&env);
    printf("%s</body></html>\n", response);

    free(response); // Free the allocated memory for the rendered content
    return 0;
}