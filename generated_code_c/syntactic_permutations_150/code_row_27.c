#include <stdio.h> 

// Function to insert username and message into database
void insert_user_message_in_db(char *username, char *message) {
   printf("Inserting %s and %s in the database\n", username, message);
}

// Function called when user submits a message
void post() { 
    // Get the username and message from the request
    char *username = "John Doe"; 
    char *message = "Hello World!";
    
    insert_user_message_in_db(username, message);
}