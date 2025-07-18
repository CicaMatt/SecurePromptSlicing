#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "http_request.h" 
#include "http_response.h" 

struct HttpRequest {
    char *url;
};

struct HttpResponse {
    int status_code;
    char *body;
};

void redirect_invalid_url(HttpRequest *req, HttpResponse *res) {
    if (strstr(req->url, "example.com") == NULL) {
        res->status_code = 403;
        res->body = "Invalid URL";
    } else {
        res->status_code = 302;
        res->body = req->url;
    }
}