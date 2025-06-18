#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
    char *username;
    char *password;
};

int login(char *username, char *password) {
    struct user users[] = {{"admin", "1234"}, {"user", "5678"}};

    for (size_t i = 0; i < sizeof(users); i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char username[20];
    char password[20];

    printf("Enter Username: ");
    scanf("%s", &username);
    printf("Enter Password: ");
    scanf("%s", &password);

    if (login(username, password) == 1) {
        printf("Logged In");
    } else {
        printf("Invalid Credentials. Please try again.");
    }
    return 0;
}