#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *method;
    char *path;
} Request;

void get_request(Request *req) {
    req->method = "GET";
}

void post_request(Request *req) {
    req->method = "POST";
}

void handle_request(Request *req, void (*handler)(Request *)) {
    handler(req);
}

void index(Request *req) {
    if (strcmp(req->method, "GET") == 0 && strcmp(req->path, "/index") == 0) {
        printf("Handling GET request for /index\n");
    }
}

void user_page(Request *req) {
    if (strcmp(req->method, "GET") == 0 && strcmp(req->path, "/user") == 0) {
        printf("Handling GET request for /user\n");
    }
}

void admin_page(Request *req) {
    if (strcmp(req->method, "GET") == 0 && strcmp(req->path, "/admin") == 0) {
        printf("Handling GET request for /admin\n");
    }
}

void do_login(Request *req) {
    if (strcmp(req->method, "POST") == 0 && strcmp(req->path, "/login") == 0) {
        printf("Handling POST request for /login\n");
    }
}

int main() {
    Request req1 = {0}, req2 = {0}, req3 = {0}, req4 = {0}, req5 = {0};
    get_request(&req1);
    req1.path = "/index";
    handle_request(&req1, index);

    post_request(&req2);
    req2.path = "/login";
    handle_request(&req2, do_login);

    get_request(&req3);
    req3.path = "/user";
    handle_request(&req3, user_page);

    get_request(&req4);
    req4.path = "/admin";
    handle_request(&req4, admin_page);

    return 0;
}