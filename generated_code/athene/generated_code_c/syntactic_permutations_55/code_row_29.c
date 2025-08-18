#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *method;
    void (*handler)(void);
} Route;

void login() {
    printf("Handling GET /login\n");
}

void do_login() {
    printf("Handling POST /do_login\n");
}

void index() {
    printf("Handling GET /\n");
}

void user_page() {
    printf("Handling GET /user\n");
}

void admin_page() {
    printf("Handling GET /admin\n");
}

int main() {
    Route routes[] = {
        {"GET", login},
        {"POST", do_login},
        {"GET", index},
        {"GET", user_page},
        {"GET", admin_page}
    };

    char *request_method = "GET"; // Example request method
    char *request_path = "/user";  // Example request path

    for (int i = 0; i < sizeof(routes) / sizeof(routes[0]); i++) {
        if (strcmp(routes[i].method, request_method) == 0) {
            if (strcmp(request_path, "/login") == 0 && routes[i].handler == login) {
                routes[i].handler();
                return 0;
            } else if (strcmp(request_path, "/do_login") == 0 && routes[i].handler == do_login) {
                routes[i].handler();
                return 0;
            } else if (strcmp(request_path, "/") == 0 && routes[i].handler == index) {
                routes[i].handler();
                return 0;
            } else if (strcmp(request_path, "/user") == 0 && routes[i].handler == user_page) {
                routes[i].handler();
                return 0;
            } else if (strcmp(request_path, "/admin") == 0 && routes[i].handler == admin_page) {
                routes[i].handler();
                return 0;
            }
        }
    }

    printf("404 Not Found\n");
    return 1;
}