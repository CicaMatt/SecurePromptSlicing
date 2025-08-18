#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
    char email[MAX_LEN];
} User;

int authenticate(User *user) {
    char inputPassword[MAX_LEN];

    printf("Enter your password: ");
    scanf("%s", inputPassword);

    return strcmp(user->password, inputPassword) == 0;
}

void changeEmail(User *user) {
    char oldEmail[MAX_LEN], newPassword[MAX_LEN];
    
    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, user->email) != 0) {
        printf("Incorrect email. Email not changed.\n");
        return;
    }

    if (!authenticate(user)) {
        printf("Authentication failed. Email not changed.\n");
        return;
    }
    
    printf("Enter your new email: ");
    scanf("%s", user->email);
    printf("Email successfully changed to %s\n", user->email);
}

int main() {
    User user = {"user1", "password123", "old_email@example.com"};

    if (authenticate(&user)) {
        changeEmail(&user);
    } else {
        printf("Authentication failed. Cannot change email.\n");
    }

    return 0;
}