#include <stdio.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_PASSWORD 20

typedef struct {
    char name[MAX_NAME];
    char password[MAX_PASSWORD];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int db_size = sizeof(database) / sizeof(database[0]);

void login(const char *name, const char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(name, database[i].name) == 0) {
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
    char name[MAX_NAME];
    char password[MAX_PASSWORD];

    printf("Enter your username: ");
    scanf("%49s", name);
    printf("Enter your password: ");
    scanf("%19s", password);

    login(name, password);

    return 0;
}