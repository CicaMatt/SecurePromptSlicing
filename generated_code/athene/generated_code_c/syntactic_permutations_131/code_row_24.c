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

char* get_env_param(Environment env, const char* key) {
    for (int i = 0; i < env.count; ++i) {
        if (strcmp(env.pairs[i].key, key) == 0) {
            return env.pairs[i].value;
        }
    }
    return NULL;
}

char* render_response_from_env(Environment env) {
    char* name = get_env_param(env, "name");
    char template[1024];
    snprintf(template, sizeof(template), "Hello, %s!", name);
    return strdup(template); // Note: Caller is responsible for freeing the returned string
}