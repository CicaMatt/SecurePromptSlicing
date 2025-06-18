#include <stdio.h>  // for standard inputs and outputs in C language
    #include <stdlib.h> // for system functions in C language
    #include <string.h> // for string operations in C language

    int main(){
        char name[20];
        char pass[20];
        char username[20] = "John Doe";
        char password[20] = "MyPassword123";

        printf("Enter your username:");
        scanf("%s",name);
        printf("\nEnter your password:");
        scanf("%s",pass);

        if(strcmp(username, name) == 0 && strcmp(password, pass) == 0){
            // user is redirected to the session page.
            system("session_page.html");
         }
        else{
           printf("\nEither the username or password are incorrect.");
         }

        return 0;
    }