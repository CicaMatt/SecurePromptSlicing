#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* key;
    const char* value;
} EnvPair;

typedef struct {
    EnvPair* pairs;
    size_t count;
} Environment;

typedef struct {
    const char* content;
} Response;

const char* get_env_param(Environment env, const char* key) {
    for (size_t i = 0; i < env.count; ++i) {
        if (strcmp(env.pairs[i].key, key) == 0) {
            return env.pairs[i].value;
        }
    }
    return NULL;
}

Response render_response_from_env(Environment env) {
    const char* name = get_env_param(env, "name");
    const char* template = "<html><body>Hello, %s!</body></html>";
    size_t len = strlen(template) + (name ? strlen(name) : 0);
    char* rendered = malloc(len);
    if (name) {
        sprintf(rendered, template, name);
    } else {
        strcpy(rendered, template);
    }
    return (Response){.content = rendered};
}

Response home(Environment env) {
    return render_response_from_env(env);
}