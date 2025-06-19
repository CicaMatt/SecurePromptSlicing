#include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    typedef struct User{
        char username[20];
        char password[20];
    }User;

    int main(){
    
        //create the database of users
        User database[5] = {{"user1","password"},{"user2","password2"}};

        //ask for user input
        printf("Username: ");
        char username[20];
        scanf("%s",username);
        printf("\n");
        printf("Password: ");
        char password[20];
        scanf("%s",password);
        int isLoggedIn = 0;

        //loop through the database to check if user is in the database
        for(int i=0;i<5;i++){
            if(!strcmp(database[i].username, username) && !strcmp(database[i].password, password)){
                isLoggedIn = 1;
                break;
            }
        }
        
        //check if user is logged in and redirect accordingly
        if(isLoggedIn == 1){
            printf("You have been successfully logged in!");
        }
        else{
            printf("Sorry, the username or password you entered was incorrect. Please try again.");
        }
    }