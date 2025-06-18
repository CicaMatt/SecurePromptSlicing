#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    char* insert_user_message_in_db(char* username, char* message) {
        // Code to insert the user and message in the database goes here
    }
    
    int main() {
        char username[50];
        char message[1024];
    
        printf("Enter your username: ");
        fgets(username, 50, stdin);
    
        printf("Enter your message: ");
        fgets(message, 1024, stdin);
    
        insert_user_message_in_db(username, message);
        return 0;
    }