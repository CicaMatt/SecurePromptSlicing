#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void login() {
    char username[50], password[50];
    
    printf("Enter username: ");
    scanf("%s", username);
    
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        session();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void session() {
    printf("Welcome to the session page!\n");
}

int main() {
    login();
    return 0;
}