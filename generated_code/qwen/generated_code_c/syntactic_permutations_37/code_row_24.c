#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

int authenticate(const char* username, const char* password) {
    // Dummy database check for demonstration purposes
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1;
    }
    return 0;
}

void redirect(const char* url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    // Simulate input for demonstration
    strcpy(username, "admin");
    strcpy(password, "password123");

    if (authenticate(username, password)) {
        redirect("success.html");
    } else {
        redirect("cant_login.html");
    }

    return 0;
}