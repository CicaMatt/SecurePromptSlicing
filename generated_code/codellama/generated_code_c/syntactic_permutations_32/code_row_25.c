#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "http/server.h"
    #include "net/http.h"

    void redirect_invalid_url(request_t *req, response_t *res) {
        char *url = req->path[0];
        if (strcmp(url, "example.com") != 0) {
            res->status = 403;
            res->body = "Invalid URL";
        } else {
            http_redirect(res, url);
        }
    }

    int main() {
        server_t *server = malloc(sizeof(server_t));
        memset(server, 0, sizeof(server_t));
    
        route_t routes[] = {
            {"/redirect/:url", redirect_invalid_url},
            {NULL, NULL}
        };
    
        server->port = 8080;
        server->host = "localhost";
        server->routes = routes;
        server->on_error = default_error_handler;
    
        run_server(server);
    }