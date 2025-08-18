#include <stdio.h>
#include <string.h>

typedef struct {
    char *method;
    char *url;
    char *http_version;
    char *username;
} Request;

typedef struct {
    int status_code;
    const char *status_message;
    const char *content_type;
    char *body;
} Response;

void http_hello_page(Request *request, Response *response) {
    response->status_code = 200;
    response->status_message = "OK";
    response->content_type = "text/html";
    
    int username_len = strlen(request->username);
    int body_len = 6 + username_len; // Length of "hello " plus length of username
    char *body = malloc(body_len + 1); // +1 for null terminator
    
    snprintf(body, body_len + 1, "hello %s", request->username);
    
    response->body = body;
}

int main() {
    Request req = {"GET", "/greet", "HTTP/1.1", "world"};
    Response res;
    http_hello_page(&req, &res);
    printf("Status: %d %s\nContent-Type: %s\n\n%s\n", res.status_code, res.status_message, res.content_type, res.body);
    free(res.body);
    return 0;
}