#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* fetch_name_from_request(Environment *env) {
    return env->name;
}

char* fetch_template_from_environment(Environment *env) {
    return env->template;
}

char* render_template_with_name(char *template, char *name) {
    if (template == NULL || name == NULL) return NULL;

    size_t template_len = strlen(template);
    size_t name_len = strlen(name);

    // Allocate memory for the final rendered string
    char *rendered = malloc(template_len + name_len + 2); // +2 for possible space and null-terminator

    if (rendered == NULL) {
        return NULL;
    }

    char *pos = strstr(template, "%s");
    if (pos != NULL) {
        size_t offset = pos - template;

        strncpy(rendered, template, offset);
        strcpy(rendered + offset, name);
        strcpy(rendered + offset + name_len, pos + 2); // Skip the %s
    } else {
        strcpy(rendered, template);
    }

    return rendered;
}

char* render_response_from_env(Environment *env) {
    char *name = fetch_name_from_request(env);
    char *template = fetch_template_from_environment(env);

    if (name == NULL || template == NULL) {
        return "Error: Missing name or template.";
    }

    char *response = render_template_with_name(template, name);
    return response;
}

char* home(Environment env) {
    char *response = render_response_from_env(&env);
    return response;
}

int main() {
    Environment env;
    env.name = "World";
    env.template = "Hello, %s!";

    char *result = home(env);

    printf("%s\n", result);
    free(result);

    return 0;
}