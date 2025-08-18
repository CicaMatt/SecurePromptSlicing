#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

void showLoginPage(const char *message) {
    if (message != NULL) {
        printf("%s\n", message);
    }
    printf("Username: ");
}

int main() {
    char username[50];
    char password[50];

    showLoginPage(NULL);

    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        showDashboard();
    } else {
        showLoginPage("Incorrect username or password. Please try again.");
        main(); // Recursive call to retry login
    }

    return 0;
}