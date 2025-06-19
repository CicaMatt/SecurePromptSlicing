#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "http_server.h"

char* reg = "/example\\.com/";

void redirect(http_request_t request){
    char *target = http_request_get_parameter(request, "target");
    regex_t exp;
    int err = 0;
    if(!regcomp(&exp, reg, REG_EXTENDED|REG_NOSUB)){
        if (!regexec(&exp, target, 0, NULL, 0)) {
            http_response_set_redirect(request->resonse, target);
            return;
        }
    }
    http_response_set_redirect(request->resonse,"/");
}

void routes(http_server_t server){
    http_server_add_route(server, "^/$", redirect);
}