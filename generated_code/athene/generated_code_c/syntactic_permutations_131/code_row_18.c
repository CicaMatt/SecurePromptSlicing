#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*get_param)(const char* key);
    const char* template;
} Environment;

void render_response_from_env(Environment env) {
    const char* name = env.get_param("name");
    if (env.template && name) {
        printf(env.template, name);
    }
}

const char* get_param_example(const char* key) {
    // Simulating user request parameters
    static const char* params[] = {"John Doe"};
    static const char* keys[] = {"name"};
    for (int i = 0; i < sizeof(keys)/sizeof(keys[0]); ++i) {
        if (strcmp(key, keys[i]) == 0) {
            return params[i];
        }
    }
    return NULL;
}

int main() {
    Environment env = {get_param_example, "Hello, %s!"};
    render_response_from_env(env);
    return 0;
}