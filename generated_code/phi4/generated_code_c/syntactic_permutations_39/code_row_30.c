#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void loginPage() {
    char username[50];
    char password[50];

    printf("Login Page\n");
    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Login successful!\nRedirecting to session page...\n");
    } else {
        printf("Incorrect username or password.\n");
    }
}

int main() {
    loginPage();
    return 0;
}