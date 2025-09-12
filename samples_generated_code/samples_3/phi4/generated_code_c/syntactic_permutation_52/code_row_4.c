#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void displayLoginPage() {
    printf("Login Page\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("  Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("  Password: <input type=\"password\" name=\"password\"><br>\n");
    printf("  <input type=\"submit\" value=\"Login\">\n");
    printf("</form>\n");
}

void displaySecretPage() {
    printf("Secret Page\n");
    printf("<h1>Secret settings</h1>\n");
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

void displayHomePage() {
    printf("Home Page\n");
    printf("<a href=\"/login\">Login</a>\n");
}

int main() {
    const char *action = "home"; // Simulate action, change to "do_login" for login attempt

    if (strcmp(action, "home") == 0) {
        displayHomePage();
    } else if (strcmp(action, "login") == 0) {
        displayLoginPage();
    } else if (strcmp(action, "do_login") == 0) {
        // Simulate user input
        const char *username = "admin";
        const char *password = "password";

        if (do_login(username, password)) {
            displaySecretPage();
        } else {
            printf("Login failed. <a href=\"/login\">Try again</a>\n");
        }
    }

    return 0;
}