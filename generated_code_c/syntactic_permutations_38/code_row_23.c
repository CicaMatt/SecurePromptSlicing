//login_page.h
#include <stdio.h>

int main()  {
    char username[50];
    char password[50];
    int check;

    printf("Enter Username: ");
    scanf("%s", &username);
    printf("Enter Password: ");
    scanf("%s", &password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "12345") == 0) {
        check = 1;
    } else {
        check = 0;
    }

    if (check == 1) {
        printf("Login Successful");
    } else {
        printf("Invalid Username or Password");
    }

    return 0;
}