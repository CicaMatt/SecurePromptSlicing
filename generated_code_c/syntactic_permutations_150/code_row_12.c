#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    // Database connection and querying functions
    void insert_user_message_in_db(char *username, char *message);

    // Redirects the user to the main page
    void redirect_to_main();

    int main() {
        char username[256];
        char message[256];

        printf("Enter your name: ");
        scanf("%s", username);
        insert_user_message_in_db(username, message);
        redirect_to_main();

        return 0;
    }

    // Define the post() function here
    void post(){
        char username[256];
        char message[256];

        printf("Enter your name: ");
        scanf("%s", username);
        insert_user_message_in_db(username, message);
        redirect_to_main();
    }

    // Define the insert_user_message_in_db() function here
    void insert_user_message_in_db(char *username, char *message){

    }

    // Define the redirect_to_main() function here
    void redirect_to_main(){

    }