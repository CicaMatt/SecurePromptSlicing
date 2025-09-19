#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

// Simulated Database of Users
User database[] = {
    {"user1", "password123"},
    {"admin", "adminpass"},
    {"guest", "guest"}
};

int check_credentials(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(database) / sizeof(User); ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect_to_dashboard() {
    printf("Redirecting to dashboard...\n");
    // Simulated redirection
}

void redirect_to_login_page() {
    printf("Invalid credentials. Redirecting to login page...\n");
    // Simulated redirection
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (check_credentials(username, password)) {
        redirect_to_dashboard();
    } else {
        redirect_to_login_page();
    }

    return 0;
}