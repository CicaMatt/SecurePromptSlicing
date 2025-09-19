#include <stdio.h>
#include <string.h>

// Function prototypes
void login();
int do_login(const char* username, const char* password);

int main() {
    // Simulate a GET request by calling the login function
    login();

    // Simulate user input for demonstration purposes (normally this would come from HTTP POST data)
    char username[] = "admin";
    char password[] = "password";

    // Call do_login with simulated input
    int result = do_login(username, password);

    if (result == 1) {
        printf("Redirecting to admin_page...\n");
    } else {
        printf("Login failed.\n");
    }

    return 0;
}

void login() {
    // Simulate returning a form for the user to enter their username and password
    printf("<form method='POST' action='/do_login'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Password: <input type='password' name='password'><br>\n");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
}

int do_login(const char* username, const char* password) {
    // Check if the user is admin
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        return 1; // Redirect to admin_page
    }
    return 0; // Login failed
}