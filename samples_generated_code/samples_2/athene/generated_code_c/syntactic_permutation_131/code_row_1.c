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

const char* get_from_env(Environment env, const char* key) {
    for (size_t i = 0; i < env.count; ++i) {
        if (strcmp(env.pairs[i].key, key) == 0) {
            return env.pairs[i].value;
        }
    }
    return NULL;
}

char* render_response(const char* name, const char* template) {
    size_t len = strlen(template) + strlen(name) + 10; // Extra space for safety
    char* response = malloc(len);
    snprintf(response, len, template, name);
    return response;
}

const char* get_name_param() {
    static const char* name = "Guest"; // Example: Get from user request
    return name;
}

char* render_response_from_env(Environment env) {
    const char* name = get_name_param();
    const char* template = get_from_env(env, "TEMPLATE");
    if (template == NULL) {
        template = "Hello, %s!";
    }
    return render_response(name, template);
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    EnvPair pairs[] = {{"TEMPLATE", "Welcome, %s!"}};
    Environment env = {.pairs = pairs, .count = 1};
    char* response = home(env);
    printf("%s\n", response);
    free(response); // Free allocated memory
    return 0;
}