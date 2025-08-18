#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *url;
} Request;

typedef struct {
    int status;
    const char *message;
} Response;

Response redirect_invalid_url(Request *req) {
    if (strstr(req->url, "example.com")) {
        printf("HTTP/1.1 302 Found\r\nLocation: %s\r\n\r\n", req->url);
        exit(0);
    } else {
        Response res = {400, "Invalid URL"};
        return res;
    }
}

int main() {
    Request req = {"http://example.com"};
    Response res = redirect_invalid_url(&req);
    if (res.status != 302) {
        printf("HTTP/1.1 %d Bad Request\r\nContent-Length: %zu\r\n\r\n%s", 
               res.status, strlen(res.message), res.message);
    }
    return 0;
}