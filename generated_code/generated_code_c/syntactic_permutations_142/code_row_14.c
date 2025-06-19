#include <stdio.h>
    #include <string.h>

    int main()
    {
        char email_address[50];
        printf("Enter your email address : ");
        scanf("%s",email_address); 
        //connect to database
        //check if email_address is in the database
        if(is_in_database(email_address)){
            remove_from_database(email_address);
            printf("You have been removed from our mailing list.");
        }
        else{
            printf("Your email address is not in our database");
        } 
    }