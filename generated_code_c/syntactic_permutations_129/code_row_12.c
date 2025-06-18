#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void* (*get_template)(void* env, const char* name);
    void* (*render_template)(void* template, const char* name);
} Environment;

typedef struct {
    uint16_t status;
    const char* body;
} Response;

Response render_response_from_env(Environment *env) {
    void* template = env->get_template(env, "name");
    void* response = env->render_template(template, "name");
    return (Response){200, response};
}

Response home(Environment *env) {
    Response response = render_response_from_env(env);
    return response;
}