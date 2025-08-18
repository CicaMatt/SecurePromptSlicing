#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"user1", "pass1"},
    {"admin", "admin123"}
};

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < sizeof(database)/sizeof(User); i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect_to_dashboard() {
    printf("Redirecting to dashboard...\n");
}

void redirect_back() {
    printf("Invalid username or password. Redirecting back...\n");
}

int main() {
    char input_username[MAX_USERNAME_LENGTH];
    char input_password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", input_username);
    printf("Enter Password: ");
    scanf("%s", input_password);

    if (authenticate(input_username, input_password)) {
        redirect_to_dashboard();
    } else {
        redirect_back();
    }

    return 0;
}