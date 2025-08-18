#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void redirect_to_dashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirect_to_login() {
    printf("Incorrect credentials, please try again.\n");
}

int main() {
    char input_username[100];
    char input_password[100];

    printf("Enter username: ");
    fgets(input_username, sizeof(input_username), stdin);
    input_username[strcspn(input_username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = '\0';

    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        redirect_to_dashboard();
    } else {
        redirect_to_login();
    }

    return 0;
}