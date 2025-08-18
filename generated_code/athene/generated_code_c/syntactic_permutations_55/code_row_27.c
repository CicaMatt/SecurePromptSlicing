#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *method;
    void (*handler)(void);
} Route;

void login() {
    printf("Login page\n");
}

void do_login() {
    printf("Processing login...\n");
}

void index() {
    printf("Home page\n");
}

void user_page() {
    printf("User page\n");
}

void admin_page() {
    printf("Admin page\n");
}

int main() {
    Route routes[] = {
        {"GET", login},
        {"POST", do_login},
        {"GET", index},
        {"GET", user_page},
        {"GET", admin_page}
    };

    int n_routes = sizeof(routes) / sizeof(Route);

    // Simulate a request
    const char *request_method = "POST";
    const char *request_path = "/login";

    for (int i = 0; i < n_routes; i++) {
        if (strcmp(request_method, routes[i].method) == 0) {
            routes[i].handler();
            break;
        }
    }

    return 0;
}