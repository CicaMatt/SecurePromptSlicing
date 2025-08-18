#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int num_users = 2;

void login(const char *username, const char *password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            printf("Login successful! Redirecting to dashboard...\n");
            return;
        }
    }
    printf("Invalid credentials. Redirecting back to login page...\n");
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    scanf("%49s", input_username);
    printf("Enter password: ");
    scanf("%49s", input_password);

    login(input_username, input_password);

    return 0;
}