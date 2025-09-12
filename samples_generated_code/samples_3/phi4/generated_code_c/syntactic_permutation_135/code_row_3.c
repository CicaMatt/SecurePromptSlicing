#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

int checkCredentials(const char *username, const char *password) {
    return (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0);
}

void onButtonClick() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (checkCredentials(username, password)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

int main() {
    onButtonClick();
    return 0;
}