#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
const int db_size = sizeof(database) / sizeof(database[0]);

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (authenticate(username, password)) {
        printf("Login successful! Redirecting to dashboard...\n");
    } else {
        printf("Invalid credentials. Please try again.\n");
        login_page();
    }
}

int main() {
    login_page();
    return 0;
}