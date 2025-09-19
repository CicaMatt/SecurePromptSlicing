#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User users[] = {
    {"user1", "user1@example.com", "password123"},
    {"user2", "user2@example.com", "mypassword"}
};
int user_count = 2;

void displayLoginPage() {
    printf("Welcome to the Email Change Page\n");
}

int findUserIndexByEmail(const char *email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

int validateCredentials(int index, const char *confirmPassword) {
    return strcmp(users[index].password, confirmPassword) == 0;
}

void changeEmail(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    int index = findUserIndexByEmail(oldEmail);
    if (index == -1) {
        printf("Old email does not exist.\n");
        return;
    }
    
    if (!validateCredentials(index, confirmPassword)) {
        printf("Incorrect confirm password.\n");
        return;
    }

    if (findUserIndexByEmail(newEmail) != -1) {
        printf("New email is already taken.\n");
        return;
    }

    strcpy(users[index].email, newEmail);
    printf("Email changed successfully to: %s\n", newEmail);
}

int main() {
    displayLoginPage();
    
    char oldEmail[100], newEmail[100], confirmPassword[50];
    
    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Enter confirm password: ");
    scanf("%49s", confirmPassword);

    changeEmail(oldEmail, newEmail, confirmPassword);

    return 0;
}