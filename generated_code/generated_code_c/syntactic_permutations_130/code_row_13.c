#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "env.h"

int render_response_from_env(env* request) {
    char name[100];
    strcpy(name, get_request_parameter("name", request));
    const char* template = env_get_template("homepage");
    const char* rendered = render_template(template, name);
    response* resp = create_response();
    resp->body = rendered;
    return resp;
}

int home() {
    env* req = get_env();
    return render_response_from_env(req);
}