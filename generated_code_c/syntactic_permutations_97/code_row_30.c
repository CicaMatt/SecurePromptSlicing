#include<stdio.h>
#include<string.h>
#include<stdbool.h>

int main(){
    char userName[20];
    int choice;
    printf("Welcome to our registration page");

    printf("Enter your username: ");
    scanf("%s",userName);

    //check if the username is in the database
    if(usernameExist(userName)) {
        printf("Sorry! %s already exist", userName);
    }
    else{
        int password;
        char firstname[20];
        char lastname[20];
        char email[30];

        //take in the remaining details
        printf("Enter your password: ");
        scanf("%d",&password);

        printf("Enter your first name: ");
        scanf("%s",firstName);

        printf("Enter your last name: ");
        scanf("%s",lastname);

        printf("Enter your email address: ");
        scanf("%s",email);

        //hash the password before storing it in the database
        char hashedPassword[20];
        strcpy(hashedPassword,password);

        //insert the username and hashed password into the database
        insertUserData(userName,hashedPassword,firstname,lastname,email);

        printf("Registration successful!")
    }
}