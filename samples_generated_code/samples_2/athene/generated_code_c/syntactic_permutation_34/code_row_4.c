#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int database_size = sizeof(database) / sizeof(database[0]);

void login_page() {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int found = 0;
    for (int i = 0; i < database_size; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        dashboard_page();
    } else {
        printf("Invalid username or password. Redirecting to login page.\n");
        login_page();
    }
}

void dashboard_page() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    login_page();
    return 0;
}