#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_name_param(const char* request) {
    // Simulate extracting "name" parameter from a request
    const char *prefix = "name=";
    if (strncmp(request, prefix, strlen(prefix)) == 0) {
        return strdup(request + strlen(prefix));
    }
    return NULL;
}

char* get_template_from_env(const Environment* env) {
    // Simulate getting the template from an environment
    return strdup(env->template);
}

char* render_template(char* template, char* name_param) {
    // Simple string replacement for rendering "Hello, <name>!"
    if (name_param == NULL || strlen(name_param) == 0) {
        name_param = "<unknown>";
    }
    
    size_t buf_size = snprintf(NULL, 0, "%s%s", template, name_param) + 1;
    char* rendered_template = malloc(buf_size);
    if (rendered_template != NULL) {
        snprintf(rendered_template, buf_size, "%s%s", template, name_param);
        // Remove the trailing comma and space
        size_t len = strlen(rendered_template);
        if (len > 2 && rendered_template[len - 1] == '!' && rendered_template[len - 2] == ' ') {
            rendered_template[len - 2] = '\0';
        }
    }

    return rendered_template;
}

char* render_response_from_env(Environment env, const char* request) {
    char *name_param = get_name_param(request);
    char *template = get_template_from_env(&env);
    
    if (name_param == NULL || template == NULL) {
        free(name_param);
        free(template);
        return strdup("Invalid name parameter or template");
    }

    char *rendered_template = render_template(template, name_param);

    free(name_param);
    free(template);

    return rendered_template;
}

char* home(Environment env) {
    const char *request = "name=John";
    return render_response_from_env(env, request);
}

int main() {
    Environment env = {"", "Hello, "};

    char *response = home(env);
    printf("%s\n", response);

    free(response);
    return 0;
}