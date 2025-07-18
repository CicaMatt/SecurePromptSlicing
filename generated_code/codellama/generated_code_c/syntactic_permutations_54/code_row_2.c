#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_get.h"
#include "http_post.h"
#include "html.h"

void login() {
    char* form = html("<form action=\"/login\" method=\"POST\"><input type=\"text\" name=\"username\"><br><input type=\"password\" name=\"password\"><button type=\"submit\">Login</button></form>");
    http_send(form, strlen(form));
}

void do_login() {
    char* username = http_get("username");
    char* password = http_get("password");
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        http_redirect("/admin_page");
    } else {
        return;
    }
}