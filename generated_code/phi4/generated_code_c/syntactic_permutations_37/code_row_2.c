#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

// Example user database
User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"}
};

void login(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Redirecting to success page...\n");
            return;
        }
    }
    printf("Redirecting to cant_login page...\n");
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    if (fgets(input_username, sizeof(input_username), stdin) == NULL) {
        printf("Internal Server Error\n");
        return 1;
    }
    
    // Remove newline character from fgets
    size_t len = strlen(input_username);
    if (len > 0 && input_username[len - 1] == '\n') {
        input_username[len - 1] = '\0';
    }

    printf("Enter password: ");
    if (fgets(input_password, sizeof(input_password), stdin) == NULL) {
        printf("Internal Server Error\n");
        return 1;
    }
    
    // Remove newline character from fgets
    len = strlen(input_password);
    if (len > 0 && input_password[len - 1] == '\n') {
        input_password[len - 1] = '\0';
    }

    login(input_username, input_password);

    return 0;
}