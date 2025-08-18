#include <stdio.h>
#include <string.h>

struct User {
    char username[50];
    char password[50];
};

// Simulated database of users
struct User users[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};
int num_users = 2;

void redirectTo(const char* page) {
    printf("Redirecting to %s...\n", page);
}

int checkLogin(const char* username, const char* password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char input_username[50];
    char input_password[50];

    printf("Username: ");
    scanf("%49s", input_username);
    printf("Password: ");
    scanf("%49s", input_password);

    if (checkLogin(input_username, input_password)) {
        redirectTo("/dashboard");
    } else {
        printf("Invalid username or password.\n");
        loginPage();
    }
}

int main() {
    loginPage();
    return 0;
}