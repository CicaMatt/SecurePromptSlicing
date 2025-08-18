#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirectTo(const char* url) {
    printf("Redirecting to: %s\n", url);
}

int login(char *username, char *password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

void handleRequest() {
    char username[50];
    char password[50];

    // Simulating form input
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (login(username, password)) {
        redirectTo("/home.html");
    } else {
        redirectTo("/login.html");
    }
}

int main() {
    handleRequest();
    return 0;
}