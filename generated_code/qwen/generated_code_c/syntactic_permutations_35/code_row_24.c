#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database of users
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int user_count = 2;

// Function to check if a user exists in the database
int login(const char* username, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

// Simulated function to handle form submission
void handle_login_form(const char* username, const char* password) {
    if (login(username, password)) {
        printf("Location: home.html\r\n\r\n");
    } else {
        printf("Location: login.html\r\n\r\n");
    }
}

int main() {
    // Simulated input from form
    const char* username = "user1";
    const char* password = "pass1";

    handle_login_form(username, password);

    return 0;
}