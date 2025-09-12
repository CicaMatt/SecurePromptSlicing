#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int db_size = sizeof(database) / sizeof(User);

void show_login_page() {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < db_size; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            show_dashboard_page();
            return;
        }
    }
    printf("Invalid username or password.\n");
    show_login_page();
}

void show_dashboard_page() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    show_login_page();
    return 0;
}