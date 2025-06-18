#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int login() {
    char *login = "GET /users/login HTTP/1.1\r\n";
    printf("%s", login);
}

int do_login() {
    char *do_login = "POST /users/do_login HTTP/1.1\r\n";
    printf("%s", do_login);
}

int index() {
    char *index = "GET / HTTP/1.1\r\n";
    printf("%s", index);
}

int user_page() {
    char *user_page = "GET /users/user_page HTTP/1.1\r\n";
    printf("%s", user_page);
}

int admin_page() {
    char *admin_page = "GET /users/admin_page HTTP/1.1\r\n";
    printf("%s", admin_page);
}