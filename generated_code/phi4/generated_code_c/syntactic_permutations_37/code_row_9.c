#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirectTo(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int authenticate(const char* username, const char* password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

int main() {
    char username[100];
    char password[100];

    printf("Enter Username: ");
    scanf("%99s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    if (authenticate(username, password)) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }

    return 0;
}