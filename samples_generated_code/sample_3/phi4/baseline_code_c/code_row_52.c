#include <stdio.h>
#include <string.h>

// Simulated database for demonstration purposes
typedef struct {
    const char* username;
    const char* password;
} User;

User users[] = {
    {"user1", "password123"},
    {"user2", "pass456"}
};

int check_credentials(const char* username, const char* password) {
    for (size_t i = 0; i < sizeof(users)/sizeof(users[0]); ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username); // Limit input size for safety

    printf("Enter password: ");
    scanf("%49s", password); // Limit input size for safety

    if (check_credentials(username, password)) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}