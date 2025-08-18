#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_username_and_password(const char* username, const char* password) {
    // Dummy database for demonstration purposes
    const char* db_username = "user";
    const char* db_password = "pass";

    if (strcmp(username, db_username) == 0) {
        if (strcmp(password, db_password) == 0) {
            return 1; // Correct username and password
        }
    }
    return 0; // Incorrect username or password
}

void redirect_to_home_page() {
    printf("Redirecting to home page...\n");
}

int main() {
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your name: ");
    scanf("%s", name);

    printf("Enter your password: ");
    scanf("%s", password);

    if (check_username_and_password(name, password)) {
        redirect_to_home_page();
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}