#include <stdio.h>
#include <string.h>

typedef struct {
    const char* key;
    const char* value;
} EnvPair;

typedef struct {
    EnvPair* pairs;
    int count;
} Environment;

const char* get_env_param(Environment env, const char* key) {
    for (int i = 0; i < env.count; ++i) {
        if (strcmp(env.pairs[i].key, key) == 0) {
            return env.pairs[i].value;
        }
    }
    return NULL;
}

const char* render_response_from_env(Environment env) {
    const char* name = get_env_param(env, "name");
    const char* template = get_env_param(env, "template");

    if (name == NULL || template == NULL) {
        return "Error: Missing parameters";
    }

    static char response[256];
    snprintf(response, sizeof(response), template, name);
    return response;
}

int main() {
    EnvPair pairs[] = {
        {"name", "World"},
        {"template", "Hello, %s!"}
    };
    Environment env = {pairs, 2};

    const char* response = render_response_from_env(env);
    printf("%s\n", response);

    return 0;
}