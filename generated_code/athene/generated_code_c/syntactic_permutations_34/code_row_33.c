#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50

typedef struct {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
} User;

User database[MAX_USERS];
int user_count = 0;

void initialize_database() {
    strcpy(database[0].username, "user1");
    strcpy(database[0].password, "pass1");
    strcpy(database[1].username, "user2");
    strcpy(database[1].password, "pass2");
    user_count = 2;
}

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (check_credentials(username, password)) {
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