#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
} Request;

typedef struct {
    char buffer[1024];
} Response;

void http_hello_page(Request *request, Response *response) {
    snprintf(response->buffer, sizeof(response->buffer), "hello %s", request->username);
}

int main() {
    Request req = { .username = "Alice" };
    Response res;
    
    http_hello_page(&req, &res);

    printf("%s\n", res.buffer); // Output: hello Alice
    return 0;
}