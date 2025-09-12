#include <stdio.h>
#include <string.h>

void get_login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='POST'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
    printf("</body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("HTTP/1.1 303 See Other\n");
        printf("Location: /admin_page\n\n");
    } else {
        printf("Login failed.\n");
    }
}

int main() {
    // Simulated request handling
    const char *request_type = "GET";
    if (strcmp(request_type, "GET") == 0) {
        get_login_form();
    }

    // For demonstration purposes, simulate a POST request with username and password
    const char *post_username = "admin";
    const char *post_password = "adminpass";

    if (strcmp(post_username, "admin") == 0 && strcmp(post_password, "adminpass") == 0) {
        do_login(post_username, post_password);
    } else {
        printf("Invalid request.\n");
    }

    return 0;
}