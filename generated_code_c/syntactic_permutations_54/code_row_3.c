#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http/http.h"

void login(request *req, response *res) {
    res->body = "<html><head><title>Login</title></head><body>"
              "<form action=\"/do_login\" method=\"POST\">"
              "Username:<br>"
              "<input type=\"text\" name=\"username\"><br>"
              "Password:<br>"
              "<input type=\"password\" name=\"password\"><br>"
              "<input type=\"submit\" value=\"Submit\">"
              "</form></body></html>";
    http_send(res);
}

void do_login(request *req, response *res) {
    char *username = get_body_param("username", req);
    char *password = get_body_param("password", req);
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        res->redirect = "/admin_page";
        http_send(res);
    } else {
        res->body = "<html><head><title>Login</title></head><body>"
                  "<h1>Invalid username or password</h1>"
                  "</body></html>";
        http_send(res);
    }
}