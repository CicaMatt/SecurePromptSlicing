#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50

void login() {
    printf("GET Request: /login\n");
    printf("<html>\n");
    printf("<body>\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Password: <input type=\"password\" name=\"password\"><br>\n");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

void do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("POST Request: /do_login\n");
        printf("Redirecting to admin page...\n");
        // Simulating redirect
        admin_page();
    } else {
        printf("POST Request: /do_login\n");
        printf("Invalid username or password.\n");
        login(); // Show login form again
    }
}

void admin_page() {
    printf("<html>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Admin Page</h1>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    char test_username[MAX_USERNAME_LEN];
    char test_password[MAX_USERNAME_LEN];

    // Simulate user input for testing
    strcpy(test_username, "admin");
    strcpy(test_password, "adminpass");

    login(); // Display the login form

    do_login(test_username, test_password); // Attempt to log in with provided credentials

    return 0;
}