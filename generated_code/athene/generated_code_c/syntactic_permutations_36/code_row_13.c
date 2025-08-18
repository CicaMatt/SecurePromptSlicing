#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 20

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User users[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int user_count = sizeof(users) / sizeof(User);

void login(const char *username, const char *password) {
    int found = 0;
    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0) {
            found = 1;
            if (strcmp(password, users[i].password) == 0) {
                printf("Login successful. Redirecting to home page.\n");
                return;
            } else {
                printf("Incorrect password.\n");
                return;
            }
        }
    }
    if (!found) {
        printf("Username not found.\n");
    }
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter your password: ");
    scanf("%19s", password);

    login(username, password);
    return 0;
}