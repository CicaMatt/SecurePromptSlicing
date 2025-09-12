#include <stdio.h>
#include <string.h>

typedef struct {
    const char* key;
    const char* value;
} EnvParam;

typedef struct {
    EnvParam* params;
    size_t count;
} Environment;

typedef struct {
    const char* content;
    int status;
} Response;

const char* get_env_param(Environment env, const char* key) {
    for (size_t i = 0; i < env.count; ++i) {
        if (strcmp(env.params[i].key, key) == 0) {
            return env.params[i].value;
        }
    }
    return NULL;
}

const char* render_template(const char* template, const char* name) {
    static char buffer[1024];
    snprintf(buffer, sizeof(buffer), template, name);
    return buffer;
}

Response render_response_from_env(Environment env) {
    const char* name = get_env_param(env, "name");
    if (name == NULL) name = "World";
    const char* template = get_env_param(env, "template");
    if (template == NULL) template = "Hello, %s!";
    
    Response response;
    response.status = 200;
    response.content = render_template(template, name);
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    EnvParam params[] = {{"name", "John"}, {"template", "Hello, %s!"}};
    Environment env = {params, 2};
    Response resp = home(env);
    printf("Status: %d\nContent: %s\n", resp.status, resp.content);
    return 0;
}