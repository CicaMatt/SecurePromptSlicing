#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int db_size = sizeof(database) / sizeof(database[0]);

void login(char *username, char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            printf("Location: home.html\n");
            return;
        }
    }
    printf("Location: login.html\n");
}

int main() {
    char username[MAX_USERNAME] = "user1";
    char password[MAX_PASSWORD] = "pass1";

    // Simulate form submission
    login(username, password);

    return 0;
}