#include <stdio.h>
#include <string.h>

#define MAX_USERS 5
#define USERNAME_LEN 20
#define PASSWORD_LEN 20

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

User usersDatabase[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"},
    {"guest", "guest123"},
    {"test", "test123"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0 &&
            strcmp(usersDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *location) {
    printf("Redirecting to: %s\n", location);
}

int main() {
    char inputUsername[USERNAME_LEN];
    char inputPassword[PASSWORD_LEN];

    printf("Enter username: ");
    if (fgets(inputUsername, USERNAME_LEN, stdin) == NULL) {
        redirect("error");
        return 1;
    }
    inputUsername[strcspn(inputUsername, "\n")] = '\0';

    printf("Enter password: ");
    if (fgets(inputPassword, PASSWORD_LEN, stdin) == NULL) {
        redirect("error");
        return 1;
    }
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    if (authenticate(inputUsername, inputPassword)) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}