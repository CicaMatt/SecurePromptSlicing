#include <stdio.h>
    void http_hello_page(struct Request *request, struct Response *response) {
        char username[50];
        sscanf(request->body, "username=%s", username);
        fprintf(response->stream, "Hello %s", username);
    }