#include <stdio.h>
#include <string.h>

typedef struct {
    const char* key;
    const char* value;
} EnvPair;

typedef struct {
    EnvPair* pairs;
    size_t count;
} Environment;

const char* get_param(const Environment* env, const char* key) {
    for (size_t i = 0; i < env->count; ++i) {
        if (strcmp(env->pairs[i].key, key) == 0) {
            return env->pairs[i].value;
        }
    }
    return NULL;
}

const char* render_template(const char* template_str, const char* name) {
    static char rendered[1024];
    snprintf(rendered, sizeof(rendered), template_str, name);
    return rendered;
}

char* render_response_from_env(Environment env) {
    const char* name = get_param(&env, "name");
    if (name == NULL) {
        name = "World";
    }
    const char* template_str = get_param(&env, "template");
    if (template_str == NULL) {
        template_str = "Hello, %s!";
    }
    return render_template(template_str, name);
}

char* home(Environment env) {
    return render_response_from_env(env);
}