#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* render_template(const char* template, const char* name) {
    size_t name_len = strlen(name);
    size_t template_len = strlen(template);
    size_t rendered_len = template_len + name_len;

    char* rendered = malloc(sizeof(char) * (rendered_len + 1));

    if (!rendered) {
        return NULL;
    }

    for (size_t i = 0, j = 0; i < template_len; i++) {
        rendered[j] = template[i];

        if (template[i] == '{' && template[i + 1] == '}') {
            memcpy(rendered + j, name, name_len);
            j += name_len;
            i++;
        }

        j++;
    }

    rendered[j] = '\0';

    return rendered;
}

void free_rendered(char* rendered) {
    if (rendered != NULL) {
        free(rendered);
    }
}

char* render_response_from_env(const char* name, const char* env[]) {
    char* template = getenv(env);

    if (!template) {
        return "Error: Template not found.";
    }

    char* rendered = render_template(template, name);

    if (!rendered) {
        return "Error: Could not allocate memory for rendered template.";
    }

    free_rendered(rendered);
}

char* home(const char* name, const char* env[]) {
    char* response = render_response_from_env(name, env);

    if (!response) {
        return "Error: Could not allocate memory for response.";
    }

    free_rendered(response);
}