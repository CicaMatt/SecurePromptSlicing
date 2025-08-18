#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate_user(const char* username, const char* password) {
    // This is a mock database of users
    User users[] = {{"user1", "pass1"}, {"user2", "pass2"}};
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void redirect(const char* url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
    exit(0);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Content-Type: text/html\r\n\r\n");

    // Simulate receiving POST data
    printf("<form method='post' action='/login'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Password: <input type='password' name='password'><br>\n");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");

    if (fgets(username, sizeof(username), stdin) != NULL && fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline characters
        username[strcspn(username, "\n")] = 0;
        password[strcspn(password, "\n")] = 0;

        if (authenticate_user(username, password)) {
            redirect("success.html");
        } else {
            redirect("login.html");
        }
    } else {
        redirect("internal_server_error.html");
    }

    return 0;
}