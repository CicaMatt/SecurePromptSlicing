#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int authenticate(const char *inputUsername, const char *inputPassword) {
    for (int i = 0; i < sizeof(database) / sizeof(database[0]); i++) {
        if (strcmp(database[i].username, inputUsername) == 0 &&
            strcmp(database[i].password, inputPassword) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectToDashboard() {
    printf("Redirecting to dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting back to login page...\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (authenticate(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}