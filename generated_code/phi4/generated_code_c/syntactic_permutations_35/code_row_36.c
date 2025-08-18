#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulate a database with hardcoded data
typedef struct {
    char* username;
    char* password;
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int check_login(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users) / sizeof(User); ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login_request(const char *username, const char *password) {
    if (check_login(username, password)) {
        printf("Login successful. Redirecting to home page...\n");
        // Simulate redirect to the home page
        system("echo 'Welcome to your dashboard!' > output.txt"); // Simulate redirection by writing a message to a file
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        // Simulate redirect back to the login page
        system("echo '<html><body><h1>Login Failed</h1><p>Redirecting to <a href=\"login.html\">Login Page</a></p></body></html>' > output.txt"); // Simulate redirection by writing HTML response to a file
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    handle_login_request(username, password);

    // Simulate opening the output file in a browser (for demonstration purposes)
    system("echo 'Output written to output.txt. You can open this file in your web browser.'");

    return 0;
}


This C code simulates a login process with hardcoded user data and uses text files as a means of simulating redirections, which are typical in web applications but not directly applicable within C programs.