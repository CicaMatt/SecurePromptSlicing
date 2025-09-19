#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* key;
    const char* value;
} Parameter;

typedef struct {
    Parameter* params;
    size_t param_count;
} Environment;

typedef struct {
    char* content;
} Template;

typedef struct {
    char* body;
} Response;

char* get_parameter(Environment *env, const char* key) {
    for (size_t i = 0; i < env->param_count; ++i) {
        if (strcmp(env->params[i].key, key) == 0) {
            return env->params[i].value;
        }
    }
    return NULL;
}

Template* get_template(Environment *env) {
    // Simplified: Assume template is always the same for this example
    static Template tmpl = { .content = "Hello, %s!" };
    return &tmpl;
}

Response* render_response_from_env(Environment *env) {
    const char* name = get_parameter(env, "name");
    if (!name) name = "World";

    Template *tmpl = get_template(env);
    size_t len = strlen(tmpl->content) + strlen(name) + 1;
    char *body = malloc(len);
    sprintf(body, tmpl->content, name);

    Response *response = malloc(sizeof(Response));
    response->body = body;

    return response;
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    // Example usage
    Parameter params[] = { {"name", "User"} };
    Environment env = { .params = params, .param_count = 1 };

    Response *response = home(&env);
    printf("%s\n", response->body);

    free(response->body);
    free(response);

    return 0;
}