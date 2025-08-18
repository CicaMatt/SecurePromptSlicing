#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void redirectTo(const char *page) {
    printf("Redirecting to %s\n", page);
}

int checkCredentials(const char *username, const char *password) {
    return (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (checkCredentials(username, password)) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }

    return 0;
}