#include <stdio.h>
#include <stdlib.h>
#include "http/server.h"

void render_template(char *name, char *template) {
    printf("%s", template);
}

void handle_request(struct request *req, struct response *res) {
    char name[128];
    sprintf(name, "%s", req->query_params["name"]);
    render_template(name, "Hello, <b>%s</b>!");
}
