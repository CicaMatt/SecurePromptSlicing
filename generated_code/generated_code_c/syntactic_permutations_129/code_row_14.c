#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "htmlrenderer.h"
#include "httpresponse.h"
#include "httprequest.h"

typedef struct {
    char* name;
} Env;

char *render_response_from_env(Env env) {
    char *name = env.name;
    HtmlRenderer *renderer = new_htmlrenderer();
    renderer->load("hello.html");
    char *content = renderer->render(name);
    free(renderer);
    return content;
}

char *home(Env env) {
    HttpRequest* req = get_current_request();
    char *name = req->get_param("name");
    env.name = name;
    char *content = render_response_from_env(env);
    HttpResponse *res = new_httpresponse(200);
    res->set_body(content);
    free(req);
    free(res);
    return content;
}