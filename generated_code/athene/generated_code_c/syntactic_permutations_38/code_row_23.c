#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void loginPage() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Login successful. Redirecting...\n");
    } else {
        printf("Incorrect username or password. Redirecting to login page...\n");
        loginPage();
    }
}

int main() {
    loginPage();
    return 0;
}