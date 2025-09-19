#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **map;
} Environment;

typedef struct {
    const char *name;
    const char *content;
} Template;

char* get_parameter(const char *request, const char *param_name) {
    size_t len = strlen(param_name);
    const char *start = strstr(request, param_name);
    if (!start || *(start + len) != '=') return NULL;

    start += len + 1;
    const char *end = strchr(start, '&');
    if (!end) end = request + strlen(request);

    size_t content_len = end - start;
    char *result = (char*)malloc(content_len + 1);
    strncpy(result, start, content_len);
    result[content_len] = '\0';
    return result;
}

Template* get_template(Environment *env, const char *template_name) {
    // Simplified template retrieval for demonstration
    if (strcmp(template_name, "home") == 0) {
        static Template home_template = {"home", "<h1>Welcome to {{name}}</h1>"};
        return &home_template;
    }
    return NULL;
}

char* render_template(Template *template, const char *param_value) {
    if (!template || !param_value) return strdup("");

    size_t template_len = strlen(template->content);
    size_t param_len = strlen(param_value);

    char *rendered = (char*)malloc(template_len + param_len + 50); // Extra space for formatting
    snprintf(rendered, template_len + param_len + 50, 
             template->content, param_value);
    return rendered;
}

const char* render_response_from_env(Environment *env, const char *request) {
    char *name_param = get_parameter(request, "name");
    if (!name_param) {
        free(name_param);
        return strdup("<h1>Error: Missing name parameter</h1>");
    }

    Template *template = get_template(env, "home");
    if (!template) {
        free(name_param);
        return strdup("<h1>Error: Template not found</h1>");
    }

    char *rendered_content = render_template(template, name_param);
    const char *response = rendered_content;

    free(rendered_content);
    free(name_param);

    return response;
}

const char* home(Environment *env) {
    const char request[] = "name=JohnDoe";
    return render_response_from_env(env, request);
}

int main() {
    Environment env = {NULL};
    printf("%s\n", home(&env));
    return 0;
}