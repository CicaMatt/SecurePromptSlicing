#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define PASSWORD "pass456"

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirect("success");
    } else if (username[0] != '\0' || password[0] != '\0') {
        redirect("cant_login");
    } else {
        redirect("internal_server_error");
    }

    return 0;
}