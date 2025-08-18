#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"admin", "password123"},
    {"user1", "userpass"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users)/sizeof(users[0]); i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: /home.html\n");
        printf("\n");
    } else {
        printf("Location: /login.html?error=1\n");
        printf("\n");
    }
}

int main() {
    char username[50], password[50];
    // Simulate form submission
    strcpy(username, "admin");  // Replace with actual form data retrieval
    strcpy(password, "password123"); // Replace with actual form data retrieval

    login(username, password);
    return 0;
}