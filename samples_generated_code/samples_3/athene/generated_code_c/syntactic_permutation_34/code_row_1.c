#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50

typedef struct {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
} User;

User database[MAX_USERS];
int user_count = 0;

void initialize_database() {
    strcpy(database[user_count].username, "user1");
    strcpy(database[user_count++].password, "pass1");

    strcpy(database[user_count].username, "user2");
    strcpy(database[user_count++].password, "pass2");
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
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        dashboard();
    } else {
        printf("Invalid credentials. Please try again.\n");
        login_page();
    }
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    initialize_database();
    login_page();
    return 0;
}