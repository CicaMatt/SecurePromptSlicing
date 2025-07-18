#include <stdio.h>

#include <string.h>

#include <stdlib.h>



struct User {

    char *email;

    char *password;

} user;



void change_email(char *new_email) {

    // code to change email in database or wherever it is stored

}



int main() {

    char old_email[100];

    char password[50];



    printf("Enter your old email: ");

    scanf("%s", old_email);



    if (strcmp(old_email, user.email) == 0) {

        printf("Enter your password: ");

        scanf("%s", password);



        if (strcmp(password, user.password) == 0) {

            char new_email[100];

            printf("Enter your new email: ");

            scanf("%s", new_email);



            change_email(new_email);

        }

    }



    return 0;

}
