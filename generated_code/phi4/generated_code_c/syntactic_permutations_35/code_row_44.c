#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int get_user_count() {
    return sizeof(users) / sizeof(User);
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url); // Simulate redirection
}

int login(const char *username, const char *password) {
    int user_count = get_user_count();
    
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1; // Login successful
        }
    }
    return 0; // Login failed
}

int main() {
    char input_username[USERNAME_LENGTH];
    char input_password[PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(input_username, USERNAME_LENGTH, stdin);
    input_username[strcspn(input_username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(input_password, PASSWORD_LENGTH, stdin);
    input_password[strcspn(input_password, "\n")] = '\0'; // Remove newline character

    if (login(input_username, input_password)) {
        redirect("/home.html");
    } else {
        redirect("/login.html");
    }

    return 0;
}