#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    // defining a structure for storing the username and password
    struct person{
        char name[10];
        char password[8];
    };
    int main(int argc, char const *argv[])
    {   // declaring an array of structures for storing the user credentials
        struct person p[5] = {{.name="sarah",.password="abc"},{.name="john",.password="12345678"}};
        // printing the login page
        printf("Enter username: ");
        char usernm[10];
        scanf("%s",usernm);
        //printing the password
        printf("Enter password: ");
        char passwrd[8];
        scanf("%s",passwrd);
        // checking for valid credentials
        int check=0;
        for(int i=0;i<sizeof(p)/sizeof(p[0]);i++)
        {   if(strcmp(usernm,p[i].name)==0 && strcmp(passwrd,p[i].password)==0){
                check=1;
                break;
            }
        }
        // printing the result of the login attempt
        if(check){
            printf("Welcome to the session page!");
        }
        else{
            printf("Username or password is incorrect");
        }
    return 0;
    }