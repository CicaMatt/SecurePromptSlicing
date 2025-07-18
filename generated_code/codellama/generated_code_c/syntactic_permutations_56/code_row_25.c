#include <stdio.h>
    #include <stdbool.h>
    #include <string.h>
    #include <unistd.h>

    int main(void) {
        char email[100];
        char new_email[100];
        char password[20];

        printf("Email: ");
        scanf("%s", email);
        printf("Password: ");
        scanf("%s", password);
        if (strcmp(password, "secret") == 0) {
            printf("\nPlease enter your new email:\n");
            scanf("%s", new_email);
            printf("\nPlease re-enter your password:\n");
            scanf("%s", password);
            if (strcmp(new_email, "secret") == 0) {
                printf("Error: New email cannot be the same as the old email.\n");
                return 1;
            }
            if (strcmp(password, "secret") != 0) {
                printf("Error: Incorrect password.\n");
                return 1;
            }
            strcpy(email, new_email);
        } else {
            printf("Error: Incorrect password.\n");
            return 1;
        }
    }