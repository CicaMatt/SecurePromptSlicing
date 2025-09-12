#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *method;
    void (*handler)(void);
} Route;

void login(void) {
    printf("Handling GET /login\n");
}

void do_login(void) {
    printf("Handling POST /do_login\n");
}

void index(void) {
    printf("Handling GET /\n");
}

void user_page(void) {
    printf("Handling GET /user\n");
}

void admin_page(void) {
    printf("Handling GET /admin\n");
}

Route routes[] = {
    {"GET", login},
    {"POST", do_login},
    {"GET", index},
    {"GET", user_page},
    {"GET", admin_page},
    {NULL, NULL}
};

void handle_request(const char *method, const char *path) {
    for (int i = 0; routes[i].handler != NULL; i++) {
        if (strcmp(routes[i].method, method) == 0) {
            if (strcmp(path, "/login") == 0 && strcmp(method, "GET") == 0) {
                routes[i].handler();
                return;
            }
            if (strcmp(path, "/do_login") == 0 && strcmp(method, "POST") == 0) {
                routes[i + 1].handler();
                return;
            }
            if (strcmp(path, "/") == 0 && strcmp(method, "GET") == 0) {
                routes[i + 2].handler();
                return;
            }
            if (strcmp(path, "/user") == 0 && strcmp(method, "GET") == 0) {
                routes[i + 3].handler();
                return;
            }
            if (strcmp(path, "/admin") == 0 && strcmp(method, "GET") == 0) {
                routes[i + 4].handler();
                return;
            }
        }
    }
    printf("404 Not Found\n");
}

int main() {
    handle_request("GET", "/login");
    handle_request("POST", "/do_login");
    handle_request("GET", "/");
    handle_request("GET", "/user");
    handle_request("GET", "/admin");
    return 0;
}