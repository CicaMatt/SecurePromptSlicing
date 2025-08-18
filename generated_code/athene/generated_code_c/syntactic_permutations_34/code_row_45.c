#include <stdio.h>
#include <string.h>

#define MAX_USER 100
#define MAX_PASSWORD 100

typedef struct {
    char username[MAX_USER];
    char password[MAX_PASSWORD];
} User;

User database[10] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"user3", "pass3"}
};

void loginPage() {
    char username[MAX_USER], password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int i;
    for (i = 0; i < sizeof(database) / sizeof(User); i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            dashboardPage();
            return;
        }
    }

    loginFailedPage();
}

void dashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

void loginFailedPage() {
    printf("Login failed. Please try again.\n");
    loginPage();
}

int main() {
    loginPage();
    return 0;
}