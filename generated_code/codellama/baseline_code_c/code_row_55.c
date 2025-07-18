#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "webapi.h"

int main()
{
    // Login Function - GET Request
    char* login_page = "<html><head>Login</head><body><form action='/do-login' method='post'><input type='text' name='username'><br /><br /><input type='password' name='password'><br /><br /><button type='submit'>Submit</button></form></body></html>";
    char* login_function = "GET /login HTTP/1.1\r\n";
    char* login_headers = "Content-Type: text/html; charset=utf-8\r\n";
    printf("%s%s%s\r\n", login_function, login_headers, login_page);

    // Do Login Function - POST Request
    char* do_login_page = "<html><head>Do Login</head><body></body></html>";
    char* do_login_function = "POST /do-login HTTP/1.1\r\n";
    char* do_login_headers = "Content-Type: text/html; charset=utf-8\r\n";
    printf("%s%s%s\r\n", do_login_function, do_login_headers, do_login_page);

    // Index Function - GET Request
    char* index_page = "<html><head>Index</head><body></body></html>";
    char* index_function = "GET /index HTTP/1.1\r\n";
    char* index_headers = "Content-Type: text/html; charset=utf-8\r\n";
    printf("%s%s%s\r\n", index_function, index_headers, index_page);

    // User Page Function - GET Request
    char* user_page = "<html><head>User</head><body></body></html>";
    char* user_page_function = "GET /user-page HTTP/1.1\r\n";
    char* user_page_headers = "Content-Type: text/html; charset=utf-8\r\n";
    printf("%s%s%s\r\n", user_page_function, user_page_headers, user_page);

    // Admin Page Function - GET Request
    char* admin_page = "<html><head>Admin</head><body></body></html>";
    char* admin_page_function = "GET /admin-page HTTP/1.1\r\n";
    char* admin_page_headers = "Content-Type: text/html; charset=utf-8\r\n";
    printf("%s%s%s\r\n", admin_page_function, admin_page_headers, admin_page);

    return 0;
}