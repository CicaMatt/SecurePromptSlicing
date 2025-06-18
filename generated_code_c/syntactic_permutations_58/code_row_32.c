#include <stdio.h> 
#include <stdlib.h> 
int main() {
char email[25], pass[16];

    printf("Enter your email: ");
    scanf("%s", &email);
    printf("Enter your password: ");
    scanf("%s", &pass);

    if (strcmp(email, "user@example.com") == 0 && strcmp(pass, "password123") == 0) {
        printf("You are logged in.\n");
        printf("Enter your new email: ");
        scanf("%s", &email);

        if (strcmp(email, "user@example.com") != 0) {
            printf("Your email was changed.\n");
        } else {
            printf("Your email was not changed.\n");
        }
    } else {
        printf("Incorrect login information.");
    }
return 0;
}