#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_server.h"

struct request {
    const char* method;
    const char* path;
    const char* body;
};

struct response {
    int statusCode;
    const char* statusMessage;
    const char* contentType;
    const char* body;
}

void processRequest(const struct request* req, struct response* resp) {
    if (strcmp(req->method, "POST") != 0) {
        resp->statusCode = 405;
        resp->body = "";
        return;
    }

    char* type = strtok(req->body, "&");
    char* payload = strtok(NULL, "=");
    if (strcmp(type, "payload") != 0) {
        resp->statusCode = 400;
        resp->body = "";
        return;
    }

    if (strcmp(payload, "create") == 0) {
        resp->statusCode = 501;
        resp->body = "not implemented";
        return;
    }
}