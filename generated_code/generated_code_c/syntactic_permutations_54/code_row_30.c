#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "httpd.h"

void login(struct http_request *req, struct http_response *res)
{
    // Set the response status and content type.
    res->status = 200;
    res->content_type = "text/html";

    // Write a simple HTML form to the body of the response.
    char *body = "<form action=\"/do_login\" method=\"post\">
                      <label for=\"username\">Username:</label>
                      <input type=\"text\" id=\"username\" name=\"username\"><br>
                      <label for=\"password\">Password:</label>
                      <input type=\"password\" id=\"password\" name=\"password\">
                  </form>";
    http_response_write_body(res, body, strlen(body));
}

void do_login(struct http_request *req, struct http_response *res)
{
    // Get the username and password from the request form data.
    const char *username = http_request_get_form_value(req, "username");
    const char *password = http_request_get_form_value(req, "password");

    // Check if the user is an admin. If not, redirect to the login page.
    if (strcmp(username, "admin") != 0 || strcmp(password, "password123") != 0)
    {
        http_response_redirect(res, "/login");
        return;
    }

    // Set the response status and content type.
    res->status = 200;
    res->content_type = "text/html";

    // Write a simple HTML page to the body of the response.
    char *body = "<h1>Welcome, Admin!</h1>";
    http_response_write_body(res, body, strlen(body));
}