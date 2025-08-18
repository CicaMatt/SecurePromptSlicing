#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Function prototypes
void login();
int do_login(const char *username, const char *password);

int main() {
    // Simulating a GET request to the login function
    login();

    // Simulating form submission with POST request
    char username[MAX_USERNAME_LENGTH] = "admin";
    char password[MAX_PASSWORD_LENGTH] = "admin123";

    do_login(username, password);

    return 0;
}

void login() {
    printf("GET /login\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='POST'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
    printf("</body></html>");
}

int do_login(const char *username, const char *password) {
    printf("POST /do_login\n");

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Redirecting to admin page...\n");
    } else {
        printf("Login failed. Not an admin.\n");
    }

    return 0;
}