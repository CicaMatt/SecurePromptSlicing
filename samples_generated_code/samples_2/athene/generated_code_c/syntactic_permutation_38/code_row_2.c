#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void loginPage() {
    char username[100], password[100];
    
    printf("Enter username: ");
    scanf("%99s", username);
    
    printf("Enter password: ");
    scanf("%99s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Incorrect username or password. Please try again.\n");
        loginPage();
    }
}

int main() {
    loginPage();
    return 0;
}