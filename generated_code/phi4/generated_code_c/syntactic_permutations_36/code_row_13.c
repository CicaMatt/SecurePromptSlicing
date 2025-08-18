#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database entries for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int num_users = 2;

void login(char *username, char *password) {
    int found = 0;
    
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            found = 1;
            if (strcmp(users[i].password, password) == 0) {
                printf("Login successful! Redirecting to home page...\n");
            } else {
                printf("Password incorrect. Please try again.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Username does not exist.\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    login(username, password);

    return 0;
}