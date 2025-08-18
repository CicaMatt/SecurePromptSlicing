#include <stdio.h>
#include <string.h>

#define MAX_USER 100
#define MAX_PASS 50

typedef struct {
    char username[MAX_USER];
    char password[MAX_PASS];
} User;

User users[] = {
    {"john", "1234"},
    {"jane", "5678"}
};

int login(char *username, char *password) {
    for (int i = 0; i < sizeof(users)/sizeof(users[0]); i++) {
        if (strcmp(username, users[i].username) == 0) {
            if (strcmp(password, users[i].password) == 0) {
                printf("Login successful. Redirecting to home page.\n");
                return 1;
            } else {
                printf("Incorrect password.\n");
                return 0;
            }
        }
    }
    printf("Username not found.\n");
    return 0;
}

int main() {
    char username[MAX_USER], password[MAX_PASS];
    
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}