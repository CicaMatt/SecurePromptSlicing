#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* (*get)(const void*, const char*);
} Environment;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Environment env, const char* request) {
    const char* name = env.get(request, "name");
    const char* template = env.get(NULL, "template");
    char buffer[256];
    sprintf(buffer, template, name);
    return (Response){.content = buffer};
}

Response home(Environment env, const char* request) {
    return render_response_from_env(env, request);
}