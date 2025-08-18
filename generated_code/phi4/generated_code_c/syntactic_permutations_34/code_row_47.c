#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

// Simulated database of users
User userDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int getUserIndex(const char *username) {
    for (int i = 0; i < sizeof(userDatabase) / sizeof(User); i++) {
        if (strcmp(userDatabase[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

void login(const char *username, const char *password) {
    int index = getUserIndex(username);
    
    if (index != -1 && strcmp(userDatabase[index].password, password) == 0) {
        printf("Login successful! Redirecting to dashboard...\n");
    } else {
        printf("Invalid username or password. Please try again.\nRedirecting back to login page...\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}