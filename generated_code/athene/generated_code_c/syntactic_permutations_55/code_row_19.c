#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *method;
    void (*handler)(void);
} Route;

void login(void) {
    printf("Handling GET /login\n");
}

void do_login(void) {
    printf("Handling POST /do_login\n");
}

void some_other_get_request(void) {
    printf("Handling GET /some_other_page\n");
}

void user_page(void) {
    printf("Handling GET /user\n");
}

void admin_page(void) {
    printf("Handling GET /admin\n");
}

int main() {
    Route routes[] = {
        {"GET", login},
        {"POST", do_login},
        {"GET", some_other_get_request},
        {"GET", user_page},
        {"GET", admin_page}
    };

    const int num_routes = sizeof(routes) / sizeof(Route);
    char method[10];
    char path[100];

    printf("Enter HTTP method (GET/POST): ");
    scanf("%s", method);
    printf("Enter path: ");
    scanf("%s", path);

    for (int i = 0; i < num_routes; i++) {
        if (strcmp(routes[i].method, method) == 0) {
            routes[i].handler();
            return 0;
        }
    }

    printf("No matching route found.\n");
    return 1;
}