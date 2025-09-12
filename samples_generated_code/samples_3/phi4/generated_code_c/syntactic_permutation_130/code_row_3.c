#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* request_parameters;
    const char* templates;
} Environment;

char* get_name_parameter(const char* params) {
    static char name[256];
    if (sscanf(params, "name=%255[^&]", name) == 1) {
        return name;
    }
    return "";
}

const char* get_template(const char* templates, const char* path) {
    return strstr(templates, path);
}

char* render_template(const char* template_content, const char* name) {
    size_t buffer_size = strlen(template_content) + strlen(name) + 1;
    char* response = malloc(buffer_size);
    if (response != NULL) {
        sprintf(response, "%s", template_content);
        char* placeholder_pos = strstr(response, "{{name}}");
        if (placeholder_pos != NULL) {
            memmove(placeholder_pos + strlen(name), placeholder_pos, strlen(placeholder_pos));
            memcpy(placeholder_pos, name, strlen(name));
        }
    }
    return response;
}

char* render_response_from_env(Environment env) {
    const char* params = env.request_parameters;
    const char* templates = env.templates;

    const char* template_path = "/home.html";
    const char* template_content = get_template(templates, template_path);
    
    if (template_content == NULL || strlen(template_content) < 1000) { // Assuming a valid template has significant content.
        return strdup("Error: Template not found.");
    }

    const char* name_param = get_name_parameter(params);

    if (strlen(name_param) == 0) {
        return strdup("Error: Name parameter missing.");
    }

    return render_template(template_content, name_param);
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {
        .request_parameters = "name=John",
        .templates = "/home.html:<html><body>Hello, {{name}}!</body></html>"
    };

    char* response = home(env);
    printf("%s\n", response);

    free(response);
    return 0;
}