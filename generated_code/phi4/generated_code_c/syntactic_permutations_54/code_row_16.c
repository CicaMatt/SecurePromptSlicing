#include <stdio.h>
#include <string.h>

// Mock function for handling GET requests (login page)
void login() {
    printf("GET /login\n");
    printf("<html>\n"
           "<body>\n"
           "<form action='/do_login' method='POST'>\n"
           "Username: <input type='text' name='username'><br>\n"
           "Password: <input type='password' name='password'><br>\n"
           "<input type='submit' value='Login'>\n"
           "</form>\n"
           "</body>\n"
           "</html>\n");
}

// Mock function for handling POST requests (login action)
void do_login(const char *username, const char *password) {
    // Check if the user is admin
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("GET /admin_page\n");
    } else {
        printf("Login failed.\n");
    }
}

int main() {
    // Simulate a GET request to login page
    login();

    // Simulate user input for POST request
    const char *username = "admin";
    const char *password = "admin123";

    // Call do_login function with simulated input
    do_login(username, password);

    return 0;
}