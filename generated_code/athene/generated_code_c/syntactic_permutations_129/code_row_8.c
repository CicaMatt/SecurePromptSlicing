#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    char *content;
} Response;

Response* create_response(const char *content) {
    Response *response = (Response *)malloc(sizeof(Response));
    if (response == NULL) return NULL;
    response->content = strdup(content);
    return response;
}

const char* get_template(Environment *env) {
    // Dummy implementation for template fetching
    const char *template_str = "<html><body>Hello, %s!</body></html>";
    return template_str;
}

Response* render_response_from_env(Environment *env) {
    const char *name = env->name;
    if (name == NULL || name[0] == '\0') {
        name = "World";
    }
    const char *template = get_template(env);
    int len = strlen(template) + strlen(name) + 1;
    char *rendered = (char *)malloc(len);
    snprintf(rendered, len, template, name);
    return create_response(rendered);
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"John"};
    Response *response = home(&env);
    printf("%s\n", response->content);
    free(response->content);
    free(response);
    return 0;
}