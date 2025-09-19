#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("\n");
}

int main() {
    char username[100], password[100];
    
    printf("Content-Type: text/html\n\n");

    if (fgets(username, sizeof(username), stdin) == NULL ||
        fgets(password, sizeof(password), stdin) == NULL) {
        redirect("/internal_server_error");
        return 1;
    }

    username[strcspn(username, "\n")] = '\0';
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirect("/success");
    } else {
        redirect("/cant_login");
    }

    return 0;
}