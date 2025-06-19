#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login_page.h"

int main() {
    char username[50];
    char password[50];
    printf("Enter Username : ");
    scanf("%s", username);
    printf("Enter Password : ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Redirecting to Dashboard");
        system("dashboard.c");
    } else {
        printf("Incorrect Username and Password.");
        system("login_page.c");
    }
    return 0;
}