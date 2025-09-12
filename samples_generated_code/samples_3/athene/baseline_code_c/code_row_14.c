#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login(char *username, char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Location: /admin_page\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Login failed. Please try again.</p>");
        printf("</body></html>");
    }
}

int main() {
    // Simulate the GET request for login form
    if (getenv("REQUEST_METHOD") != NULL && strcmp(getenv("REQUEST_METHOD"), "GET") == 0) {
        login();
    } else if (getenv("REQUEST_METHOD") != NULL && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        // Simulate the POST request for do_login
        char username[100], password[100];
        int content_length = atoi(getenv("CONTENT_LENGTH"));

        if (content_length > 0) {
            fread(username, sizeof(char), content_length, stdin);
            sscanf(username, "username=%[^&]&password=%s", username, password);
            do_login(username, password);
        }
    }

    return 0;
}