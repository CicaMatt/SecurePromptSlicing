#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<form method='post' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'></form>");
}

void do_login() {
    char username[MAX_USERNAME] = "";
    char password[MAX_PASSWORD] = "";

    // Simulate reading from POST request
    const char *post_data = getenv("QUERY_STRING");
    if (sscanf(post_data, "username=%50[^&]&password=%50s", username, password) != 2) {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Login failed</h1>");
        return;
    }

    // Simulate admin credentials
    const char *admin_username = "admin";
    const char *admin_password = "admin123";

    if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0) {
        printf("Location: /admin_page\n");
        printf("Content-Type: text/html\n\n");
        printf("<h1>Welcome to the Admin Page</h1>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Login failed</h1>");
    }
}