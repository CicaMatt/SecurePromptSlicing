#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} Form;

int check_mod(Form form) {
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    if (strcmp(form.username, correct_username) == 0 && strcmp(form.password, correct_password) == 0) {
        return 1; // true
    } else {
        return 0; // false
    }
}

int main() {
    Form form;
    printf("Enter username: ");
    scanf("%49s", form.username);
    printf("Enter password: ");
    scanf("%49s", form.password);

    if (check_mod(form)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}