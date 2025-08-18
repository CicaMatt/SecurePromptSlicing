#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void loginPage() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter Username: ");
    scanf("%49s", inputUsername);

    printf("Enter Password: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        printf("Login successful. Redirecting to session page...\n");
        // Functionality for the session page can be added here
    } else {
        printf("Incorrect username or password.\n");
    }
}

int main() {
    loginPage();
    return 0;
}