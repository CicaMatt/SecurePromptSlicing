#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "http_module.h"
#include "template_module.h"

int hello(struct HttpRequest* request, struct HttpResponse* response) {
    const char* username = request->pathVariables[0];
    response->body = template_render("hello.html", username);
    return 200;
}

void bind_url() {
    http_bind("/hello/<username>", &hello);
}