#include <stdio.h>
#include <string.h>

// Simulating a simple database with hardcoded credentials
#define USERNAME "user123"
#define PASSWORD "pass456"

void redirect_to(const char *location) {
    printf("Redirecting to: %s\n", location);
}

int main() {
    char input_username[50];
    char input_password[50];

    // Get username and password from user input
    printf("Enter username: ");
    scanf("%49s", input_username);

    printf("Enter password: ");
    scanf("%49s", input_password);

    // Check credentials against "database"
    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        redirect_to("success");
    } else {
        redirect_to("cant_login");
    }

    return 0;
}