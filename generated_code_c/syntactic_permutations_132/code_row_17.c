#include <stdio.h>
#include <stdlib.h>
#include "http/request.h"
#include "http/response.h"
#include "http/routes.h"
#include "templates/engine.h"

void hello(Request *request, Response *response) {
    char *username = request->url_params[0];
    char *template = read_file("hello.html");
    response->body = render_template(template, username);
}

int main() {
    register_route("/hello/<username>", hello);
    start_server();
    return 0;
}