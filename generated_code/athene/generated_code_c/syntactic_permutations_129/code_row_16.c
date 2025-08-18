#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Env;

typedef struct {
    const char *content_type;
    const char *body;
} Response;

Response render_response_from_env(Env *env) {
    const char *name = env->name ? env->name : "World";
    char body[1024];
    snprintf(body, sizeof(body), "<html><head><title>Greeting</title></head><body><h1>Hello, %s!</h1></body></html>", name);
    return (Response){"text/html", body};
}

Response home(Env *env) {
    Response resp = render_response_from_env(env);
    return resp;
}