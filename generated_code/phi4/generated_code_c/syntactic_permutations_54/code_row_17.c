#include <stdio.h>
#include <string.h>

const char* admin_username = "admin";
const char* admin_password = "password";

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void do_login(const char* username, const char* password) {
    if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Login failed. Please try again.\n");
    }
}

int main(int argc, char *argv[]) {
    // Simulating a GET request to the login page
    if (argc == 1 || strcmp(argv[1], "GET") == 0) {
        login();
    }

    // Simulating a POST request with username and password from form data
    else if (argc > 3 && strcmp(argv[1], "POST") == 0) {
        do_login(argv[2], argv[3]);
    }

    return 0;
}
