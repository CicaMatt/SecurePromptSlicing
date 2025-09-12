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

const char* get_param(Environment env, const char* key) {
    for (size_t i = 0; i < env.count; ++i) {
        if (strcmp(env.pairs[i].key, key) == 0) {
            return env.pairs[i].value;
        }
    }
    return "";
}

const char* render_template(const char* template_str, const char* name) {
    static char rendered[256];
    snprintf(rendered, sizeof(rendered), template_str, name);
    return rendered;
}

const char* render_response_from_env(Environment env) {
    const char* name = get_param(env, "name");
    const char* template = get_param(env, "template");
    if (strcmp(template, "") == 0) {
        template = "Hello, %s!";
    }
    return render_template(template, name);
}

const char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    EnvPair pairs[] = {{"name", "World"}, {"template", "Hello, %s!"}};
    Environment env = {pairs, 2};
    const char* response = home(env);
    printf("%s\n", response);
    return 0;
}