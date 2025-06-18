//loginpage.c
    #include <stdio.h>
    int main()
    {
        char oldEmail[100]; 
        char newEmail[100];
        char password[50];
        char confirmPassword[50];
        int isValidated = 0;
        printf("Enter your current email: ");
        scanf("%s", oldEmail);
        printf("Enter a new email: ");
        scanf("%s", newEmail);
        if(strcmp(oldEmail, newEmail) == 0){
            printf("The new email must be different from the old email");
        }
        else{
            isValidated = 1;
        }
        if(isValidated){
            printf("Enter your password: ");
            scanf("%s", password);
            printf("Confirm password: ");
            scanf("%s", confirmPassword);
            if(strcmp(password, confirmPassword) == 0){
                isValidated = 1;
            }
            else{
                isValidated = 0;
            }
        }
        if(isValidated){
            printf("Email changed successfully");
        }
        else{
            printf("Failed to change email, please try again");
        }
    }