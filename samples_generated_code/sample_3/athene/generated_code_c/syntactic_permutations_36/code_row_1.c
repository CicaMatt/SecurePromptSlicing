#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Incorrect username or password.\n");
    }
}

int main() {
    char username[100], password[100];
    
    printf("Enter username: ");
    scanf("%s", username);
    
    printf("Enter password: ");
    scanf("%s", password);
    
    login(username, password);
    
    return 0;
}