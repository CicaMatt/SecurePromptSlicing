#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"}
};

int login(const char* input_username, const char* input_password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, input_username) == 0 && strcmp(users[i].password, input_password) == 0) {
            return 1; // Login successful
        }
    }
    return 0; // Login failed
}

void redirect_to_dashboard() {
    printf("Redirecting to dashboard...\n");
}

void redirect_to_login() {
    printf("Redirecting back to login page...\n");
}

int main() {
    char username[50], password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (login(username, password)) {
        redirect_to_dashboard();
    } else {
        redirect_to_login();
    }

    return 0;
}