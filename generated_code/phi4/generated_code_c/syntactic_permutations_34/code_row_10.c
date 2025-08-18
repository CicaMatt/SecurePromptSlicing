#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define PASSWORD "pass456"

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Invalid credentials, please try again.\n");
}

int main() {
    char enteredUsername[50];
    char enteredPassword[50];

    printf("Enter Username: ");
    scanf("%49s", enteredUsername);
    
    printf("Enter Password: ");
    scanf("%49s", enteredPassword);

    if (strcmp(enteredUsername, USERNAME) == 0 && strcmp(enteredPassword, PASSWORD) == 0) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}