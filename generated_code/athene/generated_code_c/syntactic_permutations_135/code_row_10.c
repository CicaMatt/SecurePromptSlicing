#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

int check_mod(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    char username[50], password[50];
    
    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);
    
    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }
    
    return 0;
}