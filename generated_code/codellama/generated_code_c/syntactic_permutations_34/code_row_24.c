#include <stdio.h>
#include <string.h>

char username[50] = "admin";
char password[50] = "password123";

void dashboardPage() {
    printf("You have successfully logged in. Welcome to the dashboard page");
}

void loginPage() {
    char enteredUsername[50];
    char enteredPassword[50];
    printf("Enter Username: ");
    scanf("%s", enteredUsername);
    printf("Enter Password: ");
    scanf("%s", enteredPassword);
    
    if(strcmp(enteredUsername, username) == 0 && strcmp(enteredPassword, password) == 0){
        dashboardPage();
    } else {
        printf("Invalid credentials. Please try again");
        loginPage();
    }
}

int main() {
    loginPage();
    return 0;
}