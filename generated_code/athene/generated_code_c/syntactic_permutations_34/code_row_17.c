#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User database[] = {
    {"admin", "password123"},
    {"user1", "pass456"}
};

int authenticate(char *username, char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(User); i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void show_login_page() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        show_dashboard();
    } else {
        printf("Invalid credentials. Please try again.\n");
        show_login_page();
    }
}

void show_dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    show_login_page();
    return 0;
}