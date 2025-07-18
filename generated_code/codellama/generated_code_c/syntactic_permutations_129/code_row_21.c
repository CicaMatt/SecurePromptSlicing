#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "http/http.h"
#include "renderer/renderer.h"

struct response* render_response_from_env(struct env *env) {
    char *template = env->get("template", env);
    struct request *request = env->get("request", env);
    char *name = request->params["name"];
    char *content = renderer.render(template, name);
    free(template);
    free(request);
    return new_response(200, content, "text/html");
}

struct response* home(struct env *env) {
    struct response *resp = render_response_from_env(env);
    free(env);
    return resp;
}