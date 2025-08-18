#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

int authenticateUser(const User* user, const char* oldEmail, const char* password) {
    return strcmp(user->email, oldEmail) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User* user, const char* newEmail) {
    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User user = {"example@example.com", "password123"};
    char oldEmail[MAX_EMAIL], password[MAX_PASSWORD], newEmail[MAX_EMAIL];
    
    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    
    printf("Enter your password: ");
    scanf("%s", password);
    
    if (authenticateUser(&user, oldEmail, password)) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        changeEmail(&user, newEmail);
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
    
    return 0;
}