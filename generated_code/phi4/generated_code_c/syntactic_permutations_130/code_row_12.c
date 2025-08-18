#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    size_t template_len = strlen(template);
    size_t name_len = strlen(name);

    // Allocate memory for the result with some extra space
    char *result = malloc(template_len + name_len + 1);
    if (result == NULL) {
        return NULL;
    }

    int i, j;
    for (i = 0, j = 0; i < template_len; ++i) {
        if (template[i] == '{' && strncmp(&template[i], "{name}", 6) == 0) {
            strcpy(&result[j], name);
            j += name_len;
            i += 5; // Skip past the {name} in the template
        } else {
            result[j++] = template[i];
        }
    }

    result[j] = '\0';
    return result;
}

char* render_response_from_env(const Environment *env) {
    char *rendered_template = render_template(env->template, env->name);
    if (rendered_template == NULL) {
        return "Error rendering template";
    }
    
    // Allocate memory for the response
    size_t response_len = strlen(rendered_template) + 1;
    char *response = malloc(response_len);
    if (response == NULL) {
        free(rendered_template);
        return "Error allocating memory for response";
    }

    strcpy(response, rendered_template);
    free(rendered_template); // Free the intermediate result
    return response;
}

char* home(const Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World", .template = "Hello, {name}!" };

    char *response = home(&env);
    if (response != NULL) {
        printf("%s\n", response);
        free(response); // Free the response string
    }

    return 0;
}