#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment env, const char *name) {
    if (env.name == NULL || name == NULL) {
        return (Response){.content = "Hello, World!"};
    }
    size_t len = strlen(env.name) + strlen(name) + 20;
    char *buffer = malloc(len);
    snprintf(buffer, len, "Hello %s from %s!", name, env.name);
    Response resp = {.content = buffer};
    return resp;
}

Response home(Environment env) {
    const char *name = getenv("USER_NAME"); // Assuming USER_NAME is set in the environment
    if (name == NULL) {
        name = "Guest";
    }
    return render_response_from_env(env, name);
}