#include <stdio.h>
#include <string.h>

#define MAX_USER 50
#define MAX_PASS 50

typedef struct {
    char username[MAX_USER];
    char password[MAX_PASS];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int db_size = sizeof(database) / sizeof(database[0]);

void login(const char *username, const char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(username, database[i].username) == 0) {
            if (strcmp(password, database[i].password) == 0) {
                printf("Login successful. Redirecting to home page.\n");
                return;
            } else {
                printf("Incorrect password.\n");
                return;
            }
        }
    }
    printf("User not found.\n");
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