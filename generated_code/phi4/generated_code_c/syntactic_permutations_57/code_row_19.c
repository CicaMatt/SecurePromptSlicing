#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char username[MAX_LENGTH];
    char email[MAX_LENGTH];
    char password[MAX_LENGTH];
} User;

int authenticate(User users[], int numUsers, const char *email, const char *password) {
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

void changeEmail(User users[], int *numUsers, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    for (int i = 0; i < *numUsers; ++i) {
        if (strcmp(users[i].email, oldEmail) == 0 && strcmp(users[i].password, confirmPassword) == 0) {
            strcpy(users[i].email, newEmail);
            printf("Email changed successfully!\n");
            return;
        }
    }
    printf("Failed to change email. Incorrect credentials.\n");
}

int main() {
    User users[10];
    int numUsers = 1;

    // Initial user setup
    strcpy(users[0].username, "JohnDoe");
    strcpy(users[0].email, "john@example.com");
    strcpy(users[0].password, "password123");

    char oldEmail[MAX_LENGTH], newEmail[MAX_LENGTH], confirmPassword[MAX_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Enter your confirm password: ");
    fgets(confirmPassword, MAX_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    int userIndex = authenticate(users, numUsers, oldEmail, confirmPassword);

    if (userIndex != -1) {
        printf("Enter new email: ");
        fgets(newEmail, MAX_LENGTH, stdin);
        newEmail[strcspn(newEmail, "\n")] = '\0';
        
        changeEmail(users, &numUsers, oldEmail, newEmail, confirmPassword);
    } else {
        printf("Authentication failed. Incorrect email or password.\n");
    }

    return 0;
}