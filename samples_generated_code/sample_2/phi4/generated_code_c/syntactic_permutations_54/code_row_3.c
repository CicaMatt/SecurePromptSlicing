#include <stdio.h>
#include <string.h>

// Function declarations
void login();
int do_login(const char *username, const char *password);

int main() {
    // Simulate GET request for login page
    login();

    // Simulate POST request with username and password
    const char *username = "admin";
    const char *password = "password123";
    int result = do_login(username, password);
    
    if (result == 1) {
        printf("Redirecting to admin page...\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}

// Function to simulate a GET request for login form
void login() {
    printf("<html>\n<head><title>Login</title></head>\n<body>\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form>\n</body>\n</html>\n");
}

// Function to simulate a POST request for login
int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Admin credentials are correct
    }
    return 0; // Access denied
}