#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void redirectToSessionPage() {
    printf("Redirecting to Session Page...\n");
}

int main() {
    char correctUsername[MAX_USERNAME] = "admin";
    char correctPassword[MAX_PASSWORD] = "password123";

    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        redirectToSessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}