#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Env;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Env *env, const char* name) {
    if (name == NULL || env == NULL || env->name == NULL) {
        return (Response){.content = "Error: Missing parameters"};
    }
    char template[256];
    snprintf(template, sizeof(template), "<html><body>Hello, %s!</body></html>", name);
    return (Response){.content = strdup(template)};
}

Response home(Env *env) {
    const char* request_name = env->name;
    return render_response_from_env(env, request_name);
}