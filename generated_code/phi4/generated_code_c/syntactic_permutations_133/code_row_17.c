#include <stdio.h>
#include "bjoern.c"  // Importing Bjoern library which provides WSGI capabilities in C

static void handle_request(struct http_request *req, struct http_response *res) {
    res->status = 200;
    res->body = (char *)malloc(18);
    strcpy(res->body, "Hello, World!");
}

int main() {
    bjoern_run(handle_request, "localhost", 8080);
    return 0;
}