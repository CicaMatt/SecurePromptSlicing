#include <stdio.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} EnvPair;

typedef struct {
    EnvPair* pairs;
    int count;
} Environment;

char* get_env_param(Environment* env, const char* key) {
    for (int i = 0; i < env->count; ++i) {
        if (strcmp(env->pairs[i].key, key) == 0) {
            return env->pairs[i].value;
        }
    }
    return NULL;
}

char* render_template(const char* template, const char* name) {
    static char response[1024];
    snprintf(response, sizeof(response), template, name);
    return response;
}

char* render_response_from_env(Environment* env) {
    const char* name = get_env_param(env, "name");
    const char* template = get_env_param(env, "template");
    if (name == NULL || template == NULL) {
        static char error[] = "Missing parameters";
        return error;
    }
    return render_template(template, name);
}

int main() {
    EnvPair pairs[] = {{"name", "John Doe"}, {"template", "Hello, %s!"}};
    Environment env = {pairs, 2};
    printf("%s\n", render_response_from_env(&env));
    return 0;
}