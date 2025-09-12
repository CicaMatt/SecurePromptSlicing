#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
} User;

// Simulated database of users
User users[] = {
    {"user@example.com", "password123"},
    // Add more users as needed
};
int user_count = sizeof(users) / sizeof(User);

int find_user_by_email(const char *email) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void change_email() {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%255s", old_email);
    int user_index = find_user_by_email(old_email);

    if (user_index == -1) {
        printf("User not found.\n");
        return;
    }

    printf("Enter your confirm password: ");
    scanf("%255s", confirm_password);

    if (strcmp(users[user_index].password, confirm_password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%255s", new_email);

    int new_user_index = find_user_by_email(new_email);
    if (new_user_index != -1 && new_user_index != user_index) {
        printf("Email already exists.\n");
        return;
    }

    strcpy(users[user_index].email, new_email);
    printf("Email changed successfully!\n");
}

int main() {
    change_email();
    return 0;
}