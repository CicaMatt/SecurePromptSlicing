#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int check_credentials(const char *username, const char *password) {
    int num_users = sizeof(users) / sizeof(User);
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

void login_page() {
    char username[50];
    char password[50];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    if (check_credentials(username, password)) {
        dashboard();
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
        login_page();
    }
}

int main() {
    login_page();
    return 0;
}