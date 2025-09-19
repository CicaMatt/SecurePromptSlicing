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

int main() {
    for (int i = 0; routes[i].method != NULL; ++i) {
        printf("Method: %s - Path: /%s\n", routes[i].method, 
               i == 0 ? "login" : 
               i == 1 ? "do_login" : 
               i == 2 ? "" : 
               i == 3 ? "user" : 
               "admin");
        routes[i].handler();
    }
    return 0;
}