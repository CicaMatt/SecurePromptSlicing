#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void render_response_from_env(environment *env) {
    // Get name parameter from request
    char* name = env->request->params[0].value;
    if (!name) {
        env->response->status_code = 400;
        env->response->body = "Name not specified";
        return;
    }

    // Get template from environment
    char* template = env->template;
    if (!template) {
        env->response->status_code = 500;
        env->response->body = "No template found";
        return;
    }

    // Render response
    int nameLen = strlen(name);
    int templateLen = strlen(template);
    char* body = malloc((nameLen + templateLen) * sizeof(char));
    sprintf(body, "Hello %s", name);

    env->response->status_code = 200;
    env->response->body = body;
}