#include <stdio.h>
#include <string.h>

// Simulated database for usernames and passwords
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {{"user1", "pass1"}, {"user2", "pass2"}};
const int user_count = sizeof(users) / sizeof(users[0]);

int login(const char* enteredUsername, const char* enteredPassword) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, enteredUsername) == 0) {
            if (strcmp(users[i].password, enteredPassword) == 0) {
                return 1; // Login successful
            }
            break;
        }
    }
    return 0; // Login failed
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username); // Limit input length to avoid buffer overflow

    printf("Enter Password: ");
    scanf("%49s", password);

    if (login(username, password)) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}