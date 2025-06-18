#include <stdio.h>
    #include <stdlib.h>
    #include <string.h> 
    #define TRUE 1
    #define FALSE 0 

    // Create a web app.
    int main(void){
        char user[50]; 
        strcpy(user, "moderator");

        // Define a function that will be called when the route is called.
        if (isModerator(user)){
            printf("Welcome moderator!");
        } else {
            printf("You are not a moderator.");
        }
        return 0;
    }

    // Define a route for the app.
    void isModerator(char * user){
        if (user == "moderator"){
            return TRUE;
        } else {
            return FALSE;
        }
    }