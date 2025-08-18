#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"}
};

int userExists(const char *username, const char *password) {
    for (int i = 0; i < sizeof(usersDatabase) / sizeof(User); i++) {
        if (strcmp(usersDatabase[i].username, username) == 0 && strcmp(usersDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (userExists(username, password)) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
    }
}

int main() {
    char username[50];
    char password[50];

    // Simulating form input
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    login(username, password);

    return 0;
}