#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 100

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n"
           "<head><title>Login</title></head>\n"
           "<body>\n"
           "<form action=\"/do_login\" method=\"post\">\n"
           "Username: <input type=\"text\" name=\"username\"><br>\n"
           "Password: <input type=\"password\" name=\"password\"><br>\n"
           "<input type=\"submit\" value=\"Login\">\n"
           "</form>\n"
           "</body>\n"
           "</html>\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Location: /admin_dashboard\n\n");
    } else {
        printf("Status: 403 Forbidden\nContent-Type: text/plain\n\n"
               "Access denied.\n");
    }
}

int main() {
    // Simulate a GET request to login
    login();
    
    // Simulate POST data for do_login function
    const char *username = "admin";
    const char *password = "admin";

    printf("\n---\n"); // Separator

    // Call do_login with simulated POST parameters
    do_login(username, password);

    return 0;
}