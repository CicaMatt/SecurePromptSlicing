#include <stdio.h>
#include <string.h>

typedef struct {
    const char* key;
    const char* value;
} EnvPair;

typedef struct {
    size_t count;
    EnvPair* pairs;
} Environment;

typedef struct {
    const char* content;
    int status;
} Response;

const char* get_env_param(const Environment* env, const char* key) {
    for (size_t i = 0; i < env->count; ++i) {
        if (strcmp(env->pairs[i].key, key) == 0) {
            return env->pairs[i].value;
        }
    }
    return "";
}

Response render_response_from_env(const Environment* env) {
    const char* name = get_env_param(env, "name");
    const char* template = get_env_param(env, "template");

    size_t len = strlen(template) + strlen(name) + 10; // Extra space for formatting
    char* rendered = malloc(len);
    snprintf(rendered, len, template, name);

    Response response = { .content = rendered, .status = 200 };
    return response;
}

Response home(Environment env) {
    return render_response_from_env(&env);
}