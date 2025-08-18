#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void handle_request(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Location: success\n");
    } else if (username != NULL && password != NULL) {
        printf("Location: cant_login\n");
    } else {
        printf("Location: internal_server_error\n");
    }
}

int main() {
    char username[100], password[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    handle_request(username, password);

    return 0;
}