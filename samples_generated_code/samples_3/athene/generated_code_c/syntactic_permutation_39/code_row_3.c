#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void loginPage() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        sessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void sessionPage() {
    printf("Login successful! Welcome to the session page.\n");
}

int main() {
    loginPage();
    return 0;
}