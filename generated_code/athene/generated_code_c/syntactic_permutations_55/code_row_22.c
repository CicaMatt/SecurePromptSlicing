#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Login page\n");
}

void do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        printf("Login successful as admin\n");
    } else {
        printf("Login failed\n");
    }
}

void index() {
    printf("Index page\n");
}

void user_page() {
    printf("User page\n");
}

void admin_page() {
    printf("Admin page\n");
}