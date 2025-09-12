#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

void login(User *users, int user_count);
int authenticate(const char old_email[], const char confirm_password[]);
void changeEmail(User *user);

int main() {
    User users[] = {
        {"john_doe", "john@example.com", "password123"},
        {"jane_smith", "jane@example.com", "securepass"}
    };
    int user_count = sizeof(users) / sizeof(users[0]);

    login(users, user_count);

    return 0;
}

void login(User *users, int user_count) {
    char old_email[MAX_EMAIL_LENGTH];
    char confirm_password[PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", old_email);
    printf("Enter your password to confirm: ");
    scanf("%s", confirm_password);

    if (authenticate(old_email, confirm_password)) {
        for (int i = 0; i < user_count; ++i) {
            if (strcmp(users[i].email, old_email) == 0) {
                changeEmail(&users[i]);
                break;
            }
        }
    } else {
        printf("Authentication failed.\n");
    }
}

int authenticate(const char old_email[], const char confirm_password[]) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].email, old_email) == 0 && strcmp(users[i].password, confirm_password) == 0) {
            return 1;
        }
    }
    return 0;
}

void changeEmail(User *user) {
    char new_email[MAX_EMAIL_LENGTH];
    
    printf("Enter your new email: ");
    scanf("%s", new_email);

    if (strcmp(user->email, old_email) == 0 && strcmp(user->password, confirm_password) == 0) {
        strcpy(user->email, new_email);
        printf("Email changed successfully to %s\n", user->email);
    } else {
        printf("Failed to change email. Ensure you have entered the correct information.\n");
    }
}