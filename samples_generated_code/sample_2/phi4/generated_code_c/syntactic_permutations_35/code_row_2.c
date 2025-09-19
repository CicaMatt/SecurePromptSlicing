#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS];
int user_count = 0;

// Mock database check function
int login(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

// Mock function to simulate form data reception
void receive_form_data(char *username, char *password) {
    // In a real application, this would be replaced with actual form handling code.
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';
}

int main() {
    // Predefined users in the mock database
    strcpy(users[0].username, "user1");
    strcpy(users[0].password, "pass1");

    strcpy(users[1].username, "user2");
    strcpy(users[1].password, "pass2");

    user_count = 2;

    char username[50];
    char password[50];

    receive_form_data(username, password);

    if (login(username, password)) {
        printf("Redirecting to home page...\n");
        // In a real web application, this would redirect the user.
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
        // In a real web application, this would redirect the user.
    }

    return 0;
}