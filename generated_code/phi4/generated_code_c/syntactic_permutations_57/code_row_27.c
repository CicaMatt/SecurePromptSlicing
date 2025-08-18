#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
} User;

User currentUser = {"user1", "oldemail@example.com"};
char confirmCode[] = "123456";

int isLoggedIn(const char* currentEmail) {
    return strcmp(currentUser.email, currentEmail) == 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirm[MAX_EMAIL_LENGTH];
    
    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    
    if (!isLoggedIn(oldEmail)) {
        printf("Incorrect email. You are not logged in.\n");
        return;
    }
    
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    
    printf("Enter confirmation code: ");
    scanf("%s", confirm);

    if (strcmp(confirm, confirmCode) != 0) {
        printf("Incorrect confirmation code.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to %s\n", currentUser.email);
}

int main() {
    char userEmail[MAX_EMAIL_LENGTH];
    
    printf("Enter your email: ");
    scanf("%s", userEmail);

    if (isLoggedIn(userEmail)) {
        changeEmail();
    } else {
        printf("You are not logged in.\n");
    }

    return 0;
}