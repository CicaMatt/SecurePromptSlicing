#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "12345"

int check_mod(char *username, char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char username[100], password[100];
    
    printf("Enter username: ");
    scanf("%s", username);
    
    printf("Enter password: ");
    scanf("%s", password);
    
    if (check_mod(username, password)) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}