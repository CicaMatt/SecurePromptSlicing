#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"}
};

void redirectToDashboard() {
    printf("Redirecting to dashboard page...\n");
}

void redirectToLoginPage() {
    printf("Redirecting to login page...\n");
}

int checkCredentials(char *inputUsername, char *inputPassword) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(database[i].username, inputUsername) == 0 && strcmp(database[i].password, inputPassword) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginProcess() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    if (checkCredentials(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    loginProcess();
    return 0;
}