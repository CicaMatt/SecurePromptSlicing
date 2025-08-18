#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    const char *template;
    Request request;
} Environment;

char* render_template(const char *template, const char *name) {
    size_t name_len = strlen(name);
    size_t template_len = strlen(template);

    // Allocate memory for the rendered result
    char *rendered = malloc(template_len + name_len + 1); // +1 for null terminator

    if (rendered == NULL) {
        return NULL;
    }

    const char *name_pos = strstr(template, "{{name}}");
    
    if (name_pos != NULL) {
        size_t before_name_len = name_pos - template;

        memcpy(rendered, template, before_name_len);
        strcpy(rendered + before_name_len, name);
        strcpy(rendered + before_name_len + name_len, name_pos + 7); // 7 is the length of "{{name}}"
    } else {
        strcpy(rendered, template);
    }

    return rendered;
}

char* render_response_from_env(Environment *env) {
    const char *template = env->template;
    const char *name = env->request.name;

    if (name == NULL || template == NULL) {
        return strdup("Error: Missing required parameters");
    }
    
    char *rendered_template = render_template(template, name);

    return rendered_template ? rendered_template : strdup("Error: Template rendering failed");
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Request request = { .name = "Alice" };
    Environment env = { .template = "Hello, {{name}}!", .request = request };

    char *response = home(&env);

    printf("%s\n", response);

    free(response);  // Free the memory allocated by render_template

    return 0;
}