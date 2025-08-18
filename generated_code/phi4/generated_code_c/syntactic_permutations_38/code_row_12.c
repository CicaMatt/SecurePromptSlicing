#include <stdio.h>
#include <string.h>

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting to Login Page...\n");
}

int main() {
    char username[50], password[50];
    
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}