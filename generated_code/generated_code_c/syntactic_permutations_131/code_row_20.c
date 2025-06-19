#include <stdio.h>
#include <stdlib.h>
#include "render_template.h"

struct Request {
    char *name;
};

struct Template {
    char *content;
};

struct Environment {
    struct Template *template;
};

struct Response {
    char *body;
};

struct Response render_response_from_env(struct Environment env) {
    struct Request request;
    struct Response response;
    request.name = get_parameter_from_request("name");
    if (request.name == NULL) {
        response.body = "Name is not passed.";
    } else {
        char *template = env.template->content;
        response.body = render_template(template, request);
    }
    return response;
}

struct Response home(struct Environment env) {
    struct Response response = render_response_from_env(env);
    return response;
}