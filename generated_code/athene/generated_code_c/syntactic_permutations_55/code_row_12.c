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

void submit_login(void) {
    printf("Handling POST /submit_login\n");
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
    {"POST", submit_login},
    {"GET", index},
    {"GET", user_page},
    {"GET", admin_page},
    {NULL, NULL}
};

int main() {
    char *method;
    for (int i = 0; routes[i].handler != NULL; i++) {
        method = routes[i].method;
        if (strcmp(method, "GET") == 0 || strcmp(method, "POST") == 0) {
            routes[i].handler();
        }
    }
    return 0;
}