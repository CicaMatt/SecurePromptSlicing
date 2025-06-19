#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http/server.h"
#include "http/request.h"
#include "http/response.h"
#include "http/url_parser.h"

void redirect_invalid_url(http_request* req, http_response* res) {
    char* url = req->params["url"];
    if (strcmp(url, "example.com") == 0) {
        http_redirect(res, url);
    } else {
        http_error(res, 403, "Invalid URL");
    }
}

int main() {
    http_server* server = http_server_new("localhost", 8080);
    http_route(server, "/redirect/<url>", redirect_invalid_url);
    return 0;
}