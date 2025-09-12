#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"admin", "admin123"}
};
int user_count = 2;

void login() {
    char input_username[USERNAME_LENGTH];
    char input_password[PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", input_username);
    printf("Enter password: ");
    scanf("%s", input_password);

    int found = 0;
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].username, input_username) == 0 && strcmp(database[i].password, input_password) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Login successful. Redirecting to dashboard...\n");
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        login();
    }
}

int main() {
    printf("Welcome to the Login Page\n");
    login();
    return 0;
}