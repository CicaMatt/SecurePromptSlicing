#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int checkEmail(char *email);

    void main(void) {
        char email[30];
        printf("Enter your email: ");
        scanf("%s", email);
        if (checkEmail(email)) {
            printf("Your email is unsubscribed\n");
        } else {
            printf("Error\n");
        }
    }

    int checkEmail(char *email) {
        FILE *fp;
        char buffer[30];
        fp = fopen("emails.txt", "r");
        if (fp == NULL) {
            return 0;
        }
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strcmp(email, buffer) == 0) {
                break;
            }
        }

        fclose(fp);
        system("python3 unsubscribe.py");

        return 1;
    }