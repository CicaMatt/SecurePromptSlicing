#include <stdio.h>
#include <string.h>

#define MAX_INPUT 100

typedef struct {
    char username[MAX_INPUT];
    char password[MAX_INPUT];
    char email[MAX_INPUT];
} User;

int authenticate(User user, const char* username, const char* password) {
    return strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0;
}

void updateEmail(User *user, const char* new_email) {
    strcpy(user->email, new_email);
}

int main() {
    User currentUser = {"john_doe", "password123", "old@example.com"};
    
    char username[MAX_INPUT], password[MAX_INPUT];
    printf("Enter username: ");
    fgets(username, MAX_INPUT, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, MAX_INPUT, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (!authenticate(currentUser, username, password)) {
        printf("Incorrect username or password.\n");
        return 1;
    }

    char old_email[MAX_INPUT], new_email[MAX_INPUT], confirm_password[MAX_INPUT];
    
    printf("Enter your old email: ");
    fgets(old_email, MAX_INPUT, stdin);
    old_email[strcspn(old_email, "\n")] = '\0';
    
    if (strcmp(old_email, currentUser.email) != 0) {
        printf("Old email does not match our records.\n");
        return 1;
    }
    
    printf("Enter new email: ");
    fgets(new_email, MAX_INPUT, stdin);
    new_email[strcspn(new_email, "\n")] = '\0';
    
    if (strcmp(new_email, old_email) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }
    
    printf("Confirm your password: ");
    fgets(confirm_password, MAX_INPUT, stdin);
    confirm_password[strcspn(confirm_password, "\n")] = '\0';
    
    if (strcmp(password, confirm_password) != 0) {
        printf("Password confirmation does not match.\n");
        return 1;
    }
    
    updateEmail(&currentUser, new_email);
    printf("Email updated successfully!\n");

    return 0;
}