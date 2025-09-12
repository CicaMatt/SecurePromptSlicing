#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

void changeEmail(User *user) {
    char oldEmail[100], newPassword[50];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", newPassword);

    if (strcmp(user->email, oldEmail) == 0 && strcmp(user->password, newPassword) == 0) {
        char newEmail[100];
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Old email or password is incorrect. Email not changed.\n");
    }
}

int main() {
    User user = {"john_doe", "john@example.com", "password123"};

    char action[10], username[50], password[50];

    do {
        printf("1: Login\n2: Change Email\n3: Exit\nChoose an option: ");
        scanf("%s", action);

        if (strcmp(action, "1") == 0) {
            printf("Enter your username: ");
            scanf("%s", username);
            printf("Enter your password: ");
            scanf("%s", password);

            if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
                printf("Login successful.\n");
                do {
                    char changeAction[10];
                    printf("1: Change Email\n2: Logout\nChoose an option: ");
                    scanf("%s", changeAction);
                    
                    if (strcmp(changeAction, "1") == 0) {
                        changeEmail(&user);
                    }
                } while (strcmp(changeAction, "2") != 0);
            } else {
                printf("Login failed. Incorrect username or password.\n");
            }
        } else if (strcmp(action, "3") == 0) {
            break;
        } else {
            printf("Invalid option.\n");
        }
    } while (1);

    return 0;
}