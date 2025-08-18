#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int checkCredentials(const char *username, const char *password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);

    if (checkCredentials(username, password)) {
        redirectTo("homepage.html");
    } else {
        redirectTo("cant_login.html");
    }

    return 0;
}