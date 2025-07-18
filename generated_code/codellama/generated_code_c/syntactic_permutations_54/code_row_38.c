#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "httplib.h"

void login(httplib_request *req, httplib_response *res) {
    const char *html = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'>" 
                        "<title>Login</title></head><body><form action='/do_login'"
                        "method='POST'><input type='text' name='username'>"
                        "<input type='password' name='password'><input type='submit'>"
                        "</form></body></html>";
    httplib_send(req, res, html, strlen(html), "text/html", 200);
}

void do_login(httplib_request *req, httplib_response *res) {
    const char *username = httplib_get_field(req, "username");
    const char *password = httplib_get_field(req, "password");
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        httplib_redirect(res, "/admin_page", 302);
    } else {
        httplib_send(req, res, "<html><body>Invalid username or password</body></html>", 401);
    }
}

int main() {
    httplib_server *svr = httplib_new_server();
    httplib_set_request_handler(svr, "/login", &login);
    httplib_set_request_handler(svr, "/do_login", &do_login);
    return httplib_run(svr, "localhost", 8080);
}