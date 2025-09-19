#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int check_credentials(const char *username, const char *password) {
    // Simulated database check
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1;
    }
    return 0;
}

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Content-Type: text/html\n\n");

    if (fscanf(stdin, "username=%[^&]&password=%s", username, password) != 2) {
        redirect("/internal_server_error");
        return 1;
    }

    int result = check_credentials(username, password);
    if (result == 1) {
        redirect("/success");
    } else {
        redirect("/cant_login");
    }

    return 0;
}