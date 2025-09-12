#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "123456"

void loginPage() {
    printf("Login Page\n");
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        dashboard();
    } else {
        loginPage();
    }
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    loginPage();
    return 0;
}