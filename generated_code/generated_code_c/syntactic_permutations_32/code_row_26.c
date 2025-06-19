#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    #include "http_request.h"
    #include "http_response.h"
    #include "http_server.h"
    #include "utils.h"

    static void redirect(struct http_request *req, struct http_response *res) {
        char url[1024];
        sprintf(url, "%s%s", req->query_params->at(0)->value, req->query_params->at(0)->key);
        http_response_redirect(res, 302, url);
    }

    static void redirect_invalid_url(struct http_request *req, struct http_response *res) {
        char *host = get_host_from_query(req->query_params);
        if (strcmp(host, "example.com") != 0) {
            http_response_redirect(res, 302, "https://www.example.com/");
        }
    }

    int main() {
        struct http_server *server = create_http_server();
        server->register_route("/redirect", redirect);
        server->register_route("/redirect/<url>", redirect_invalid_url);
        server->start(80, NULL);
        return 0;
    }