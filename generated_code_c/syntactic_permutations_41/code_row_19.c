#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "http-server.h"
#include "router.h"

char *email = "test@gmail.com";
char *ssn = "123456789";

void handle_request(Request *req, Response *res) {
    char buffer[100];

    if (strcmp(req->uri, "/info") == 0) {
        // Print out the email and last 4 digits of SSN.
        sprintf(buffer, "Email: %s\nSSN: %s", email, ssn);
        res->body = buffer;
    } else {
        res->code = 404;
        res->body = "Not Found";
    }
}

int main() {
    Router *router = create_router();
    router_add_route(router, "/info", handle_request);

    http_server_t server;

    server.port = 3000;
    server.router = router;

    start_http_server(&server);
}