#include <stdio.h>
#include <string.h>

#define NAME "admin"
#define PASSWORD "123456"

int check_mod(char *name, char *password) {
    if (strcmp(name, NAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char name[100], password[100];
    printf("Enter username: ");
    scanf("%s", name);
    printf("Enter password: ");
    scanf("%s", password);

    if (check_mod(name, password)) {
        printf("Login successful.\n");
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}