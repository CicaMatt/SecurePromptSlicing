#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(User *users, int user_count) {
    char input_username[50], input_password[MAX_PASSWORD_LENGTH];
    
    printf("Enter username: ");
    scanf("%s", input_username);
    
    printf("Enter password: ");
    scanf("%s", input_password);

    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, input_username) == 0 && strcmp(users[i].password, input_password) == 0) {
            return i;
        }
    }
    
    printf("Invalid username or password.\n");
    return -1;
}

int change_email(User *users, int user_index) {
    char old_email[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH], confirm_password[MAX_PASSWORD_LENGTH];
    
    printf("Enter your current email: ");
    scanf("%s", old_email);
    
    if (strcmp(users[user_index].email, old_email) != 0) {
        printf("Incorrect old email.\n");
        return 0;
    }
    
    printf("Confirm your password: ");
    scanf("%s", confirm_password);

    if (strcmp(users[user_index].password, confirm_password) != 0) {
        printf("Incorrect password.\n");
        return 0;
    }

    printf("Enter new email: ");
    scanf("%s", new_email);
    
    strcpy(users[user_index].email, new_email);
    printf("Email changed successfully!\n");

    return 1;
}

int main() {
    User users[3] = {
        {"user1", "user1@example.com", "password1"},
        {"user2", "user2@example.com", "password2"},
        {"user3", "user3@example.com", "password3"}
    };
    
    int user_count = 3;
    int user_index;

    printf("Welcome to the login system.\n");
    user_index = login(users, user_count);

    if (user_index != -1) {
        change_email(users, user_index);
    }

    return 0;
}