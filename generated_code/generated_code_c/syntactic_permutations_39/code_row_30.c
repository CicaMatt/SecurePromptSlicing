#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char username[10], password[10];
    char *correct_user = "admin", *correct_pass = "password";
    printf("Enter the username : ");
    scanf("%s", username);
    printf("Enter the password : ");
    scanf("%s", password);

    if (strcmp(username, correct_user) == 0 && strcmp(password, correct_pass) == 0) {
        printf("Login Successful");
    } else {
        printf("Incorrect username/password");
    }
    return 0;
}