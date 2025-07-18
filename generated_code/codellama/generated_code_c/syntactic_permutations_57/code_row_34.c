//importing needed libraries and dependencies

#include <stdio.h>

#include <stdlib.h>

#include <string.h>



int check_email(char* email, char* confirm_password)

{

    //check if the given email and password is correct or not

    int result = 0;

    char sql[256];

    strcpy(sql, "SELECT email FROM user WHERE email='%s' AND password='%s' LIMIT 1");

    mysql_real_escape_string(email);

    if (mysql_num_rows(sql) == 1)

        result = 1;

    return result;

}



int change_email(char* old_email, char* new_email, char* confirm_password)

{

    //change the email address of the user

    int result = 0;

    if (check_email(old_email, confirm_password) == 1)

    {

        char sql[256];

        strcpy(sql, "UPDATE user SET email='%s' WHERE email='%s' LIMIT 1");

        mysql_real_escape_string(new_email);

        if (mysql_query(sql) != NULL)

            result = 1;

    }

    return result;

}



int main()

{

    //inputting the old email, new email and confirm password from user

    printf("Enter your old email: ");

    char old_email[256];

    fgets(old_email, 256, stdin);

    printf("Enter your new email: ");

    char new_email[256];

    fgets(new_email, 256, stdin);

    printf("Enter confirm password: ");

    char confirm_password[256];

    fgets(confirm_password, 256, stdin);



    //checking if the email is correct or not

    int result = check_email(old_email, confirm_password);

    if (result == 1)

        printf("Email changed successfully.\n");

    else

        printf("Invalid user credentials.\n");



    return 0;

}
