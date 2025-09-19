#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send_response(const char *status, const char *content_type, const char *body) {
    printf("Status: %s\n", status);
    printf("Content-Type: %s\n", content_type);
    printf("\n");
    printf("%s\n", body);
}

void login() {
    send_response("200 OK", "text/html", "<form method='post' action='/do_login'>Username: <input type='text' name='username'><br>Password: <input type='password' name='password'><br><input type='submit'></form>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        send_response("302 Found", "text/html", "<html><body>Redirecting to admin page...</body></html>");
        printf("Location: /admin_page\n");
    } else {
        send_response("302 Found", "text/html", "<html><body>Invalid credentials, redirecting back to login...</body></html>");
        printf("Location: /login\n");
    }
}

void index() {
    send_response("200 OK", "text/html", "<h1>Welcome to the Home Page</h1><a href='/user_page'>User Page</a><br><a href='/admin_page'>Admin Page (requires login)</a>");
}

void user_page() {
    send_response("200 OK", "text/html", "<h1>User Page</h1><p>Welcome, user!</p>");
}

void admin_page() {
    send_response("200 OK", "text/html", "<h1>Admin Page</h1><p>Welcome, administrator!</p>");
}