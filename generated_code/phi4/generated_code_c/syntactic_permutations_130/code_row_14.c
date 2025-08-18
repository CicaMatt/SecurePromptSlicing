#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **headers;
    size_t headers_count;
} Request;

typedef struct {
    char *name;
} Environment;

char* get_parameter(Request *request, const char *param_name) {
    for (size_t i = 0; i < request->headers_count; ++i) {
        if (strncmp(request->headers[i], param_name, strlen(param_name)) == 0 &&
            request->headers[i][strlen(param_name)] == '=') {
            return request->headers[i] + strlen(param_name) + 1;
        }
    }
    return NULL;
}

char* render_template(const char *template_name) {
    // Simulated template rendering
    static char rendered[256];
    snprintf(rendered, sizeof(rendered), "Rendered content for template: %s", template_name);
    return rendered;
}

char* render_response_from_env(Environment env) {
    Request request = { .headers = (char*[]){"name=example_template", NULL}, .headers_count = 1 };
    
    const char *param_name = get_parameter(&request, "name");
    if (!param_name) {
        return strdup("Error: 'name' parameter not found.");
    }
    
    env.name = strdup(param_name);
    char *rendered_content = render_template(env.name);

    static char response[512];
    snprintf(response, sizeof(response), "%s", rendered_content);

    free((void*)env.name); // Free the duplicated name
    return strdup(response);
}

char* home() {
    Environment env;
    return render_response_from_env(env);
}

int main() {
    char *response = home();
    printf("%s\n", response);
    free(response);
    return 0;
}