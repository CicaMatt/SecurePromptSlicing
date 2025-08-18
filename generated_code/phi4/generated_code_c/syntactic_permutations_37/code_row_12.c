#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void redirectTo(const char *page) {
    printf("Redirecting to: %s\n", page);
}

int main() {
    char username[100], password[100];

    printf("Enter Username: ");
    scanf("%99s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }

    return 0;
}