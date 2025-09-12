#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock structure to represent HTTP requests and responses
typedef struct {
    char method[10];
    char path[100];
} HttpRequest;

typedef struct {
    char body[256];
} HttpResponse;

void login(HttpRequest *req, HttpResponse *res) {
    if (strcmp(req->method, "GET") == 0 && strcmp(req->path, "/login") == 0) {
        strcpy(res->body, "<html><body>Login Page</body></html>");
    } else {
        strcpy(res->body, "404 Not Found");
    }
}

void do_login(HttpRequest *req, HttpResponse *res) {
    if (strcmp(req->method, "POST") == 0 && strcmp(req->path, "/login") == 0) {
        // Simulate successful login
        strcpy(res->body, "<html><body>Welcome!</body></html>");
    } else {
        strcpy(res->body, "404 Not Found");
    }
}

void index(HttpRequest *req, HttpResponse *res) {
    if (strcmp(req->method, "GET") == 0 && strcmp(req->path, "/index") == 0) {
        strcpy(res->body, "<html><body>Index Page</body></html>");
    } else {
        strcpy(res->body, "404 Not Found");
    }
}

void user_page(HttpRequest *req, HttpResponse *res) {
    if (strcmp(req->method, "GET") == 0 && strcmp(req->path, "/user") == 0) {
        strcpy(res->body, "<html><body>User Page</body></html>");
    } else {
        strcpy(res->body, "404 Not Found");
    }
}

void admin_page(HttpRequest *req, HttpResponse *res) {
    if (strcmp(req->method, "GET") == 0 && strcmp(req->path, "/admin") == 0) {
        strcpy(res->body, "<html><body>Admin Page</body></html>");
    } else {
        strcpy(res->body, "404 Not Found");
    }
}

int main() {
    HttpRequest req;
    HttpResponse res;

    // Example usage
    strcpy(req.method, "GET");
    strcpy(req.path, "/login");
    login(&req, &res);
    printf("Login: %s\n", res.body);

    strcpy(req.method, "POST");
    strcpy(req.path, "/login");
    do_login(&req, &res);
    printf("Do Login: %s\n", res.body);

    strcpy(req.method, "GET");
    strcpy(req.path, "/index");
    index(&req, &res);
    printf("Index: %s\n", res.body);

    strcpy(req.method, "GET");
    strcpy(req.path, "/user");
    user_page(&req, &res);
    printf("User Page: %s\n", res.body);

    strcpy(req.method, "GET");
    strcpy(req.path, "/admin");
    admin_page(&req, &res);
    printf("Admin Page: %s\n", res.body);

    return 0;
}