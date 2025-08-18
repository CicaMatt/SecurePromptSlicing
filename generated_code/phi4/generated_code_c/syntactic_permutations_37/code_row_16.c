#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define PASSWORD "pass456"

void redirect(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int authenticate(char *username, char *password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

int main() {
    char username[50], password[50];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (authenticate(username, password)) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}