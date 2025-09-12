#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_SIZE 50
#define PASSWORD_SIZE 50

typedef struct {
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
} User;

User database[MAX_USERS];
int user_count = 0;

void initialize_database() {
    strcpy(database[0].username, "user1");
    strcpy(database[0].password, "pass1");
    user_count++;
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        dashboard_page();
    } else {
        printf("Invalid credentials. Please try again.\n");
        login_page();
    }
}

void dashboard_page() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    initialize_database();
    login_page();
    return 0;
}