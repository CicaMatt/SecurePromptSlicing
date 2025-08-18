#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='POST'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login() {
    char username[MAX_USERNAME] = "";
    char password[MAX_PASSWORD] = "";

    // Simulate reading POST data (simplified for example)
    const char *post_data = getenv("QUERY_STRING");

    if (sscanf(post_data, "username=%[^&]&password=%s", username, password) != 2) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed. Invalid input.</body></html>");
        return;
    }

    // Simulate user validation
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed. Incorrect username or password.</body></html>");
    }
}