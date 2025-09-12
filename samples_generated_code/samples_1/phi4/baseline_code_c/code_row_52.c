#include <stdio.h>
#include <string.h>

// Simple simulation of a database using static arrays
const char *usernames[] = {"user1", "admin", "guest"};
const char *passwords[] = {"pass1", "admin123", "guestpass"};

#define NUM_USERS 3

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < NUM_USERS; ++i) {
        if (strcmp(username, usernames[i]) == 0 && strcmp(password, passwords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char username[50];
    char password[50];

    // Simulate user input
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove newline character

    if (authenticate(username, password)) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}