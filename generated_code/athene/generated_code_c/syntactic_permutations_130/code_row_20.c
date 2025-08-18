#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    const char *value;
} EnvPair;

typedef struct {
    EnvPair *pairs;
    size_t count;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment env) {
    const char *name = "Unknown";
    for (size_t i = 0; i < env.count; ++i) {
        if (strcmp(env.pairs[i].key, "name") == 0) {
            name = env.pairs[i].value;
            break;
        }
    }
    size_t len = strlen(name) + 25;
    char *content = malloc(len);
    snprintf(content, len, "<h1>Hello, %s!</h1>", name);
    Response response = { .content = content };
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}