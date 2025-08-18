#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "123456"

void loginPage() {
    char username[100], password[100];
    
    printf("Enter username: ");
    scanf("%99s", username);
    
    printf("Enter password: ");
    scanf("%99s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        sessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void sessionPage() {
    printf("Welcome to the session page!\n");
}

int main() {
    loginPage();
    return 0;
}