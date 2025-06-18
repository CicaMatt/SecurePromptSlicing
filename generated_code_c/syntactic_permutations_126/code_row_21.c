#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "http_request.h"
#include "http_response.h"

void http_hello_page(http_request *req, http_response *resp)
{
    char *username = req->body;
    char *outputbuf = malloc(strlen(username) + 4096);
    sprintf(outputbuf,"<html><head><title>Hello %s!</title></head><body>Welcome, %s!</body></html>",username,username);

    resp->status_code = HTTP_STATUS_OK;
    resp->content_type = "text/html";
    resp->body = outputbuf;

    http_response_write(resp);
    http_response_close(resp);
}