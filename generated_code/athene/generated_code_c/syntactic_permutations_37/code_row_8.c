#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void redirect(const char *location) {
    printf("Location: %s\r\n", location);
    printf("Content-Type: text/html\r\n\r\n");
}

int main() {
    char username[100];
    char password[100];

    printf("Content-Type: text/html\r\n\r\n");

    if (fgets(username, sizeof(username), stdin) == NULL ||
        fgets(password, sizeof(password), stdin) == NULL) {
        redirect("/internal_server_error");
        return 1;
    }

    username[strcspn(username, "\r\n")] = '\0';
    password[strcspn(password, "\r\n")] = '\0';

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirect("/success");
    } else {
        redirect("/cant_login");
    }

    return 0;
}