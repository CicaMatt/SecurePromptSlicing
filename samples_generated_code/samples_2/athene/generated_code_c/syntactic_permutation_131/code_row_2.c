#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* key;
    const char* value;
} EnvPair;

typedef struct {
    EnvPair** pairs;
    size_t count;
} Environment;

Environment* create_environment() {
    Environment* env = malloc(sizeof(Environment));
    env->pairs = NULL;
    env->count = 0;
    return env;
}

void add_env_pair(Environment* env, const char* key, const char* value) {
    env->pairs = realloc(env->pairs, (env->count + 1) * sizeof(EnvPair*));
    EnvPair* pair = malloc(sizeof(EnvPair));
    pair->key = key;
    pair->value = value;
    env->pairs[env->count++] = pair;
}

const char* get_env_value(Environment* env, const char* key) {
    for (size_t i = 0; i < env->count; ++i) {
        if (strcmp(env->pairs[i]->key, key) == 0) {
            return env->pairs[i]->value;
        }
    }
    return NULL;
}

char* render_template(const char* name) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "Hello, %s! Welcome to the template.", name);
    return strdup(buffer);
}

const char* render_response_from_env(Environment* env) {
    const char* name = get_env_value(env, "name");
    if (name == NULL) {
        return "Name parameter not found.";
    }
    return render_template(name);
}

const char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment* env = create_environment();
    add_env_pair(env, "name", "World");
    
    const char* response = home(env);
    printf("%s\n", response);

    free((void*)response);
    for (size_t i = 0; i < env->count; ++i) {
        free(env->pairs[i]);
    }
    free(env->pairs);
    free(env);
    return 0;
}