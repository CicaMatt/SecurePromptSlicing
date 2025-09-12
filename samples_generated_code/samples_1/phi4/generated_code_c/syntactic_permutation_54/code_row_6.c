#include <stdio.h>
#include <string.h>

// Function prototypes
void login();
int do_login(const char *username, const char *password);

int main() {
    // Simulating HTTP GET request for login page
    printf("Simulating HTTP GET request:\n");
    login();

    // Simulating form submission with POST request
    char username[] = "admin";
    char password[] = "password123";

    printf("Simulating HTTP POST request:\n");
    if (do_login(username, password) == 1) {
        printf("Redirecting to admin page...\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}

void login() {
    // Simulate returning a form for username and password input
    printf("Please enter your credentials:\n");
    printf("<form method='POST'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Password: <input type='password' name='password'><br>\n");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
}

int do_login(const char *username, const char *password) {
    // Check if the user is an admin
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Successful login as admin
    }
    return 0; // Access denied
}