#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define PASSWORD "pass456"
#define MAX_LEN 100

typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
} User;

int login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0) {
        if (strcmp(password, PASSWORD) == 0) {
            printf("Login successful. Redirecting to home page.\n");
            return 1;
        } else {
            printf("Incorrect password.\n");
            return 0;
        }
    } else {
        printf("Username not found.\n");
        return 0;
    }
}

int main() {
    char username[MAX_LEN], password[MAX_LEN];
    
    printf("Enter username: ");
    scanf("%s", username);
    
    printf("Enter password: ");
    scanf("%s", password);
    
    login(username, password);

    return 0;
}