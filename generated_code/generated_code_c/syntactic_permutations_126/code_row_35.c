C 
#include <stdio.h>
#include <stdlib.h>
#include "http_server.h"

void http_hello_page(Request *request, Response *response) {
    char username[100];
    sprintf(username, "%s", request->body);

    Buffer outputbuf = new_buffer();
    buffer_appendf(&outputbuf, "<html><head><title>Hello %s</title></head>", username);
    buffer_appendf(&outputbuf, "<body><h1>Hello %s</h1></body></html>", username);

    response->write(response, outputbuf.data, outputbuf.size);
    response->close(response);
}