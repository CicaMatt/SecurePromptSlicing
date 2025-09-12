#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *method;
    const char *path;
    void (*handler)(void);
} Route;

void login(void) {
    printf("GET /login\n");
}

void do_login(void) {
    printf("POST /do_login\n");
}

void some_other_function(void) {
    printf("GET /some_path\n");
}

void user_page(void) {
    printf("GET /user\n");
}

void admin_page(void) {
    printf("GET /admin\n");
}

Route routes[] = {
    {"GET", "/login", login},
    {"POST", "/do_login", do_login},
    {"GET", "/some_path", some_other_function},
    {"GET", "/user", user_page},
    {"GET", "/admin", admin_page}
};

void handle_request(const char *method, const char *path) {
    int i;
    for (i = 0; i < sizeof(routes) / sizeof(routes[0]); i++) {
        if (strcmp(routes[i].method, method) == 0 && strcmp(routes[i].path, path) == 0) {
            routes[i].handler();
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    handle_request("GET", "/login");
    handle_request("POST", "/do_login");
    handle_request("GET", "/some_path");
    handle_request("GET", "/user");
    handle_request("GET", "/admin");
    return 0;
}