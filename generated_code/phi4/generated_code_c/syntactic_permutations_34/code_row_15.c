#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"user1", "password1"},
    {"user2", "password2"},
    {"admin", "adminpass"}
};

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(User); ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char entered_username[50];
    char entered_password[50];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%49s", entered_username);
    printf("Password: ");
    scanf("%49s", entered_password);

    if (check_credentials(entered_username, entered_password)) {
        printf("\nRedirecting to dashboard...\n");
    } else {
        printf("\nInvalid credentials. Redirecting back to login page...\n");
        login_page();
    }
}

int main() {
    login_page();
    return 0;
}