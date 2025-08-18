#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
    printf("</body></html>");
}

int check_admin(const char *username, const char *password) {
    // For demonstration purposes, hardcode an admin username and password.
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void do_login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Content-Type: text/html\n\n");
    
    // Simulate receiving POST data
    // In a real scenario, you would parse the HTTP request to get these values.
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\r\n")] = 0; // Remove newline character

    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\r\n")] = 0; // Remove newline character

    if (check_admin(username, password)) {
        printf("<html><body>");
        printf("Welcome to the admin page!");
        printf("</body></html>");
    } else {
        printf("Invalid username or password.");
    }
}

int main(int argc, char *argv[]) {
    // Simulate request handling
    if (argc > 1) {
        if (strcmp(argv[1], "GET") == 0) {
            login();
        } else if (strcmp(argv[1], "POST") == 0) {
            do_login();
        }
    }

    return 0;
}