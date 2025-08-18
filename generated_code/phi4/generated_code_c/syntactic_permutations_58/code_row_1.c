#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[50];
} User;

int login(User *users, int user_count) {
    char entered_username[50], entered_password[50];

    printf("Enter username: ");
    scanf("%49s", entered_username);
    printf("Enter password: ");
    scanf("%49s", entered_password);

    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, entered_username) == 0 &&
            strcmp(users[i].password, entered_password) == 0) {
            return i;
        }
    }

    printf("Invalid username or password.\n");
    return -1;
}

int change_email(User *users, int user_index) {
    char old_email[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH], confirmed_password[50];

    printf("Enter old email: ");
    scanf("%99s", old_email);
    printf("Confirm your password: ");
    scanf("%49s", confirmed_password);

    if (strcmp(users[user_index].email, old_email) == 0 &&
        strcmp(users[user_index].password, confirmed_password) == 0) {
        printf("Enter new email: ");
        scanf("%99s", new_email);
        strcpy(users[user_index].email, new_email);
        printf("Email changed successfully!\n");
    } else {
        printf("Old email or password is incorrect.\n");
    }
}

int main() {
    User users[10] = {
        {"user1", "user1@example.com", "pass1"},
        {"user2", "user2@example.com", "pass2"}
    };
    int user_count = 2;
    int logged_in_user_index = -1;

    while (1) {
        printf("1. Login\n");
        printf("2. Change email\n");
        printf("3. Exit\n");
        printf("Choose an option: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                logged_in_user_index = login(users, user_count);
                if (logged_in_user_index != -1)
                    printf("Login successful!\n");
                break;

            case 2:
                if (logged_in_user_index == -1) {
                    printf("Please log in first.\n");
                } else {
                    change_email(users, logged_in_user_index);
                }
                break;

            case 3:
                return 0;

            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}