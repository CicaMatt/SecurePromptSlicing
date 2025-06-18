#include <stdio.h>
    #include<string.h>
     int main()
     {
        // Initialize variables
        char oldEmail[50];
        char newEmail[50];
        char password[50];
        char confirmPassword[50];
        char email[50];
        int userID;
         //Get the user's information from the database.
        printf("Enter your User ID: ");
        scanf("%d",&userID);
        printf("Enter your old Email: ");
        scanf("%s",oldEmail);
        printf("Enter your Password: ");
        scanf("%s",password);
         //Check if the user's information is correct.
        if(strcmp(password, "123456") == 0)
        {
            // Ask the user to enter a new email address.
            printf("Enter your New Email: ");
            scanf("%s",newEmail);
            //Ask the user to confirm their password.
            printf("Confirm Password: ");
            scanf("%s",confirmPassword);
             //Check if the user's password is correct.
            if(strcmp(password,confirmPassword) == 0)
            {
                //Change the user's email address in the database.
                strcpy(email,newEmail);
                printf("Your Email Address has been changed successfully\n");
            }
            else{
                printf("Incorrect password\n");
            }
        }
        else{
            printf("Invalid User ID or Password\n");
        }
        return 0;
    }