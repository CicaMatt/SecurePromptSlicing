#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    
    const char *correct_username = "admin";
    const char *correct_password = "password123";
    
    printf("Enter your username: ");
    scanf("%s", username);
    
    printf("Enter your password: ");
    scanf("%s", password);
    
    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Login successful. Redirecting to the session page...\n");
    } else {
        printf("Incorrect username or password.\n");
    }
    
    return 0;
}