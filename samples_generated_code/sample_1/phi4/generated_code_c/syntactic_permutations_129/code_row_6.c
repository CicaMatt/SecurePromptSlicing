#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

const char* get_request_parameter(const char *env, const char *param) {
    if (strcmp(env, param) == 0) {
        return "index.html"; // Simulating a template name extraction
    }
    return NULL;
}

const char* render_template(const char *template_name) {
    if (strcmp(template_name, "index.html") == 0) {
        return "<html><body>Welcome to the Home Page!</body></html>";
    }
    return "<html><body>Template Not Found</body></html>";
}

char* render_response_from_env(Environment env) {
    const char *template_name = get_request_parameter(env.name, "name");
    if (template_name == NULL) {
        template_name = "default.html"; // Default template
    }

    const char *rendered_content = render_template(template_name);
    size_t len = strlen(rendered_content) + 1;
    char *response = malloc(len);
    if (response != NULL) {
        strncpy(response, rendered_content, len);
    }
    return response; 
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { "name=index.html" };
    char *response = home(env);

    printf("%s\n", response);

    free(response);
    return 0;
}