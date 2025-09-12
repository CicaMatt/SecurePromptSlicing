#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    char username[MAX_LEN];
    char email[MAX_LEN];
    char password[MAX_LEN];
} User;

User users[10]; // Sample user storage
int registered_users = 0;

void login() {
    char username[MAX_LEN], password[MAX_LEN];

    printf("Enter Username: ");
    scanf("%s", username);

    for (int i = 0; i < registered_users; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Enter Password: ");
            scanf("%s", password);
            
            if (strcmp(users[i].password, password) == 0) {
                updateUserEmail(username);
                return;
            } else {
                printf("Incorrect password.\n");
            }
        }
    }

    printf("User not found.\n");
}

void registerUser() {
    User newUser;

    printf("Enter Username: ");
    scanf("%s", newUser.username);

    for (int i = 0; i < registered_users; ++i) {
        if (strcmp(users[i].username, newUser.username) == 0) {
            printf("Username already taken.\n");
            return;
        }
    }

    printf("Enter Email: ");
    scanf("%s", newUser.email);

    printf("Enter Password: ");
    scanf("%s", newUser.password);

    users[registered_users++] = newUser;
}

void updateUserEmail(const char* username) {
    User *user = NULL;

    for (int i = 0; i < registered_users; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            user = &users[i];
            break;
        }
    }

    if (!user) return;

    char old_email[MAX_LEN], new_email[MAX_LEN], confirm_password[MAX_LEN];

    printf("Enter Old Email: ");
    scanf("%s", old_email);

    if (strcmp(user->email, old_email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter New Email: ");
    scanf("%s", new_email);
    
    if (strcmp(old_email, new_email) == 0) {
        printf("New email must be different from old email.\n");
        return;
    }

    printf("Confirm Password: ");
    scanf("%s", confirm_password);

    if (strcmp(user->password, confirm_password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user->email, new_email);
    printf("Email updated successfully!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                login();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}